#include "figure_print.h"
#include "sys.h"
#include "usart3.h"
#include "delay.h"
#include "beep.h"
#include "jpstm32_gpio.h"
#include "jpstm32_sysclk.h"
#include "jpstm32_nvic.h"
#include "JXL12864G-086.h"
#include "Debug_usart.h"


extern u8 Usart3Buffer[16];
extern volatile u8 UsartR_Finished;

unsigned int 	SaveNumber=0; 
unsigned int  searchnum=0;
unsigned int  SearchNumber=0;		
unsigned int 	clk0=0;

unsigned char resfifo[16];

unsigned char changeflag=0,modeflag=0,clearallflag=0;
//默认为识别模式，如果为1为录入指纹模式

//验证设备握手口令 ，发送16个，回传12个字节
unsigned char  VPWD[17]={16,0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x07,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};	

//探测手指口令并从传感器上读入图像   发送12个字节，回传12个
unsigned char  GIMG[13]={12,0xef,0x01,0xff,0xff,0xff,0xff, 0x01,0x00,0x03,0x01,0x00,0x05};

//根据原始图像生成指纹特征  发送13 ，回传12
unsigned char  GENT1[14]={13,0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x04,0x02,0x01,0x00,0x08};

//根据原始图像生成指纹特征2： 发送13 回传12
 unsigned char  GENT2[14]={13,0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x04,0x02,0x02,0x00,0x09}; 

 //以charbuffera或charbufferb中的特征文件搜索整个或部分指纹库  发17 回 16
unsigned char  SEAT[17]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x03,0xe7,0x00,0xf8};

//将charbuffera与charbufferb中的指纹特征文件合并生成模板，存于ModelBuffer中  发12回12
 unsigned char  MERG[13]={12,0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x03,0x05,0x00,0x09};

 //将ModelBuffer2中的文件存到flash指纹库中  发 15 回 12
 unsigned char  STOR[16]={15,0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x06,0x06,0x02,0x00,0x00,0x00,0x0f};
 
 //清除指纹库    发 12  回  12
 unsigned char  DELE_all[13]={12,0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x03,0x0d,0x00,0x11};

 void figure_print_init()
 {
	 usart3_init(36,9600); 
	 Beep_Init();
 }
 
 void replace()
{
		unsigned char m=0;
	UsartR_Finished = 0;
		for(m=0;m<16;m++){
		resfifo[m]= Usart3Buffer[m];
		Usart3Buffer[m]=0x00;
	}
}
 
unsigned char VefPSW(void){
	unsigned char i=0;
	
	unsigned char *p = VPWD;
	i=*p;
	p++;
	Usart3_send(i,p);
	
	while(!UsartR_Finished);
	UsartR_Finished = 0;
	replace();
	if(resfifo[9]==0x00){
		return 1;//表示口令验证正确
	}else if(resfifo[9]==0x01){
		return 2;//表示收包有错
	}else {
		return 3;//表示口令不正确
	}
}
 
unsigned char Clear_ALL(void){
	unsigned char i=0;
	unsigned char *p = DELE_all;
	i=*p;
	p++;
	Usart3_send(i,p);
	
	while(!UsartR_Finished);
	replace();
	if(resfifo[9]==0x00){
		return 1;//表示清空成功
	}else if(resfifo[9]==0x01){
		return 2;//表示收包有错
	}else {
		return 3;//表示清空失败
	}
}


unsigned char ImgProcess(unsigned char BUFID){
	unsigned char i=0;
	unsigned char m=0;
	unsigned char n=0;

	unsigned char *p = GIMG;
	unsigned char *x = GENT1;
	unsigned char *y = GENT2;

	i=*p;
	m=*x;
	n=*y;

	p++;
	x++;
	y++;
	
	Usart3_send(i,p);
	
	while(!UsartR_Finished);
	replace();
	if(resfifo[9]==0x00)
	{
			if(BUFID==1)
			{
				Usart3_send(m,x);
				while(!UsartR_Finished);
				replace();
				if(resfifo[9]==0x00){
					return 1;//成功
				}
				else
				{
					return 0;//失败
				}
			}
			else if(BUFID==2)
			{
				Usart3_send(n,y);
				while(!UsartR_Finished);
				replace();
				if(resfifo[9]==0x00){
					return 1;//成功
				}
				else
				{
					return 0;//失败
				}
			}
		
	}else if(resfifo[9]==0x01)
	{
		return 2;//表示收包有错
	}else if(resfifo[9]==0x02)
	{
		return 3;//表示传感器上无手指
	}else if(resfifo[9]==0x03)
	{
		return 4;
	}
	return 0;
}

unsigned int Searchfinger(void){
	unsigned char i=0;
	unsigned char *p = SEAT;
	
	i=*p;
	p++;
	
	Usart3_send(18,SEAT);
	
	while(!UsartR_Finished);
	replace();
	if(resfifo[9]==0x00)
	{
		SearchNumber=resfifo[10]*256+resfifo[11];
		return 1;
	}
	else
	{
		return 0;
	}

}

unsigned int search(void)
{
	unsigned  char SearchBuf=0,i=0;
	while(i<20)
	{
		Usart3_send(12,&GIMG[1]);
		while(!UsartR_Finished){}; UsartR_Finished = 0;
		if(Usart3Buffer[9] == 0x00)
		{
			Usart3_send(13,&GENT1[1]);
			while(!UsartR_Finished){}; UsartR_Finished = 0;
			if(Usart3Buffer[9] == 0x00)
			{
				Usart3_send(17,SEAT);
				while(!UsartR_Finished){}; UsartR_Finished = 0;
					if(Usart3Buffer[9] == 0x00)
						return (Usart3Buffer[10]<<8)|Usart3Buffer[11];
			}
		}
		i++;
	}
	return 0;
}

unsigned char savefingure(unsigned int ID)
{
	unsigned char i=0;
	unsigned int sum=0;
	unsigned char FIFO[80]={0};
	unsigned char m=0;
	unsigned char *n=FIFO;
	
	for(i=0;i<16;i++)
	{
		FIFO[i]=STOR[i];
	}
	
	FIFO[12]=ID/256;
	FIFO[13]=ID%256;
	
	for(i=7;i<14;i++)
	{
		sum= sum + FIFO[i];
	}
	
	FIFO[14]=sum/256;
	FIFO[15]=sum%256;
	

	m=*n;
	n++;
	
	Usart3_send(m,n);
	
	while(!UsartR_Finished);
	replace();
	if(resfifo[9]==0x00)
	{
		return 1;//存储成功
	}
	else
	{
		return 0;
	}
}

unsigned char enroll(void)
{
	unsigned char temp=0,count=0;
	while(1)
	{
		Clear_Screen_IN();
		Display_GB2312_String_IN(3,0," 开始录入");
		delayMs(1000);
		temp=ImgProcess(1);
		if(temp==1)
		{
			Clear_Screen_IN();
			Display_GB2312_String_IN(3,0," 第一次采集成功");
			count=0;
			//采集第一个特征成功
			BEEP_CONTROL = 1;
			delayMs(100);
			BEEP_CONTROL = 0;
			delayMs(2000);
			break;
		}
		else
		{
			if(temp==2)
			{
				Clear_Screen_IN();
				Display_GB2312_String_IN(3,0," 采集失败");
				Display_GB2312_String_IN(5,0,"传包错误");
				delayMs(1000);
				count++;
				if(count>=40)
					return 0;
			}
			else if(temp ==3)
			{
				Clear_Screen_IN();
				Display_GB2312_String_IN(3,0," 采集失败");
				Display_GB2312_String_IN(5,0,"传感器上无手指");
				delayMs(1000);
				count++;
				if(count>=40)
					return 0;
			}
			else if(temp==4)
			{
				Clear_Screen_IN();
				Display_GB2312_String_IN(3,0," 采集失败");
				Display_GB2312_String_IN(5,0,"指纹特征不明显");
				delayMs(1000);
				count++;
				if(count>=40)
					return 0;
			}
		}
	}
	
	delayMs(2000);
	
	while(1)
	{
		Clear_Screen_IN();
		Display_GB2312_String_IN(3,0," 开始录入");
		delayMs(1000);
		temp = ImgProcess(2);
		if(temp==1)
		{
			unsigned char i=0;
			unsigned char *p=MERG;
			Clear_Screen_IN();
			Display_GB2312_String_IN(3,0," 第二次采集成功");
			delayMs(2000);
			i=*p;
			p++;
			Usart3_send(i,p);
			while(!UsartR_Finished);
			replace();
			if(resfifo[9]==0x00)
			{	
				Clear_Screen_IN();
				Display_GB2312_String_IN(3,0," 合成模板成功");
				
				BEEP_CONTROL=1;
				delayMs(100);
				BEEP_CONTROL=0;
				delayMs(100);
				BEEP_CONTROL=1;
				delayMs(100);
				BEEP_CONTROL=0;
				delayMs(2000);
				return 1;
			}
			else
			{
				Clear_Screen_IN();
				Display_GB2312_String_IN(3,0," 合成失败");
				delayMs(1000);
				return 0;
			}
		}
		else
		{
			if(temp==2)
			{
				Clear_Screen_IN();
				Display_GB2312_String_IN(3,0," 采集失败");
				Display_GB2312_String_IN(5,0,"传包错误");
				delayMs(1000);
				count++;
				if(count>=25)
					return 0;
			}
			else if(temp ==3)
			{
				Clear_Screen_IN();
				Display_GB2312_String_IN(3,0," 采集失败");
				Display_GB2312_String_IN(5,0,"传感器上无手指");
				delayMs(1000);
				count++;
				if(count>=25)
					return 0;
			}
			else if(temp==4)
			{
				Clear_Screen_IN();
				Display_GB2312_String_IN(3,0," 采集失败");
				Display_GB2312_String_IN(5,0,"指纹特征不明显");
				delayMs(1000);
				count++;
				if(count>=25)
					return 0;
			}
		}
		
	}
	
}

