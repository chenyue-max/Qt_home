#include "figure_print.h"
#include "sys.h"
#include "usart3.h"
#include "delay.h"
#include "beep.h"
#include "jpstm32_gpio.h"
#include "jpstm32_sysclk.h"
#include "jpstm32_nvic.h"
#include "JXL12864G-086.h"
#include "rgb_led.h"
#include "lock.h"

extern u8 Usart3Buffer[16];
extern volatile u8 UsartR_Finished;


unsigned int 	SaveNumber=0; 
unsigned int  searchnum=0;
unsigned int  SearchNumber=0;		

//验证设备握手口令 ，发送16个，回传12个字节
unsigned char  VPWD[16]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x07,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};	

//探测手指口令并从传感器上读入图像   发送12个字节，回传12个
unsigned char  GIMG[12]={0xef,0x01,0xff,0xff,0xff,0xff, 0x01,0x00,0x03,0x01,0x00,0x05};

//根据原始图像生成指纹特征  发送13 ，回传12
unsigned char  GENT1[13]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x04,0x02,0x01,0x00,0x08};

//根据原始图像生成指纹特征2： 发送13 回传12
 unsigned char  GENT2[13]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x04,0x02,0x02,0x00,0x09}; 

 //以charbuffera或charbufferb中的特征文件搜索整个或部分指纹库  发17 回 16
unsigned char  SEAT[17]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x03,0xe7,0x00,0xf8};

//将charbuffera与charbufferb中的指纹特征文件合并生成模板，存于ModelBuffer中  发12回12
 unsigned char  MERG[12]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x03,0x05,0x00,0x09};

 //将ModelBuffer2中的文件存到flash指纹库中  发 15 回 12
 unsigned char  STOR[15]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x06,0x06,0x02,0x00,0x00,0x00,0x0f};
 
 //清除指纹库    发 12  回  12
 unsigned char  DELE_all[12]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x03,0x0d,0x00,0x11};

 void figure_print_init()
 {
	 RGB_LED_Init();
	// usart3_init(36,9600); 
	 usart3_init(36,57600);
	 Beep_Init();
	 Lcd_Init_IN();
 }
 
 
unsigned char VefPSW(void){
	
	
	Usart3_send(16,VPWD);
	
	while(!UsartR_Finished);
	UsartR_Finished = 0;
	
	if(Usart3Buffer[9]==0x00){
		return 1;//表示口令验证正确
	}else if(Usart3Buffer[9]==0x01){
		return 2;//表示收包有错
	}else {
		return 3;//表示口令不正确
	}
}
 
unsigned char Clear_ALL(void){
	Usart3_send(12,DELE_all);
	while(!UsartR_Finished);	
	UsartR_Finished = 0;
	
	if(Usart3Buffer[9]==0x00){
		return 1;//表示清空成功
	}else if(Usart3Buffer[9]==0x01){
		return 2;//表示收包有错
	}else {
		return 3;//表示清空失败
	}
}


unsigned char ImgProcess(unsigned char BUFID){
	//unsigned char *p = GIMG;
	//unsigned char *x = GENT1;
	//unsigned char *y = GENT2;
	Usart3_send(12,GIMG);
	while(!UsartR_Finished);
	UsartR_Finished = 0;
	if(Usart3Buffer[9]==0x00)
	{
			if(BUFID==1)
			{
				Usart3_send(13,GENT1);
				while(!UsartR_Finished);
				UsartR_Finished = 0;
				if(Usart3Buffer[9]==0x00){
					return 1;//成功
				}
				else
				{
					return 0;//失败
				}
			}
			else if(BUFID==2)
			{
				Usart3_send(13,GENT2);
				while(!UsartR_Finished);
				UsartR_Finished = 0;
				if(Usart3Buffer[9]==0x00){
					return 1;//成功
				}
				else
				{
					return 0;//失败
				}
			}
		
	}else if(Usart3Buffer[9]==0x01)
	{
		return 2;//表示收包有错
	}else if(Usart3Buffer[9]==0x02)
	{
		return 3;//表示传感器上无手指
	}else if(Usart3Buffer[9]==0x03)
	{
		return 4;
	}
	return 0;
}

unsigned int search(void)
{
	//unsigned  char SearchBuf=0;
   unsigned  char i=0;
	while(i<20)
	{
		Usart3_send(12,GIMG);
		while(!UsartR_Finished){}; UsartR_Finished = 0;
		if(Usart3Buffer[9] == 0x00)
		{
			Usart3_send(13,GENT1);
			while(!UsartR_Finished){}; UsartR_Finished = 0;
			if(Usart3Buffer[9] == 0x00)
			{
				Usart3_send(17,SEAT);
				while(!UsartR_Finished){}; UsartR_Finished = 0;
					if(Usart3Buffer[9] == 0x00)
						return (Usart3Buffer[10]<<8)|Usart3Buffer[11];
					else if(Usart3Buffer[9] == 0x09)
					{
						return 0;
					}
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
	
	for(i=0;i<15;i++)
	{
		FIFO[i]=STOR[i];
	}
	
	FIFO[11]=ID/256;
	FIFO[12]=ID%256;
	
	for(i=6;i<13;i++)
	{
		sum= sum + FIFO[i];
	}
	
	FIFO[13]=sum/256;
	FIFO[14]=sum%256;
	
	Usart3_send(15,FIFO);
	
	while(!UsartR_Finished);
	UsartR_Finished = 0;
	if(Usart3Buffer[9]==0x00)
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
				Display_GB2312_String_IN(3,0,"采集失败");
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
			Clear_Screen_IN();
			Display_GB2312_String_IN(3,0," 第二次采集成功");
			delayMs(2000);
			Usart3_send(12,MERG);
			while(!UsartR_Finished);
			UsartR_Finished = 0;
			if(Usart3Buffer[9]==0x00)
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

void input_figure()
{
		Clear_Screen_IN();//全情屏
	
		if(VefPSW()==1)
		{
			Display_GB2312_String_IN(1,0," 握手成功");
			BEEP_CONTROL=1;
			delayMs(500);
			BEEP_CONTROL=0;
				//其他操作
		}
		else
		{
				//continue;
		}
//		Clear_Screen_IN();
//		Display_GB2312_String_IN(1,0," 1 录取指纹");
//		Display_GB2312_String_IN(3,0," 2 指纹进门");
//		Display_GB2312_String_IN(5,0," 3 密码进门");
//		Display_GB2312_String_IN(7,0," 4 刷卡进门 ");
		delayMs(5000);
		if(SaveNumber<162)
		{
			R_LED=0x00;
			G_LED=0xff;
			B_LED=0xff;
			delayMs(50);
			BEEP_CONTROL=1;
			delayMs(500);
			BEEP_CONTROL=0;
			Clear_Screen_IN();
			Display_GB2312_String_IN(3,24,"请按下手指");
			delayMs(4000);
			
			if(enroll()==1)
			{
				R_LED=0xff;
				G_LED=0x00;
				B_LED=0xff;
				delayMs(500);
				Clear_Screen_IN();
				Display_GB2312_String_IN(3,24,"录入完毕");
				Display_GB2312_String_IN(3,24,"请松开手指");
				delayMs(2000);
				if(savefingure(SaveNumber+1)==1)
				{
					Clear_Screen_IN();
					Display_GB2312_String_IN(3,0,"存储成功");
					SaveNumber++;
					delayMs(100);
					BEEP_CONTROL=1;
					delayMs(100);
					BEEP_CONTROL=0;
					delayMs(3000);	
				}
			}
		}
}


int check_figure()             //识别
{
//	Clear_Screen_IN();
//	Display_GB2312_String_IN(1,0," 1 录取指纹");
//	Display_GB2312_String_IN(3,0," 2 指纹进门");
//	Display_GB2312_String_IN(5,0," 3 密码进门");
//	Display_GB2312_String_IN(7,0," 4 刷卡进门 ");
	delayMs(3000);
	R_LED=0xff;
	G_LED=0xff;
	B_LED=0x00;
	delayMs(500);
	BEEP_CONTROL=1;
	delayMs(500);
	BEEP_CONTROL=0;
	Clear_Screen_IN();
	Display_GB2312_String_IN(3,24,"请按下手指");
	delayMs(2000);			
	searchnum = search();
	if(searchnum>=1&&searchnum<=1000)
	{
		R_LED=0xff;
		G_LED=0x00;
		B_LED=0xff;
		BEEP_CONTROL=1;
		delayMs(500);
		BEEP_CONTROL=0;
		Clear_Screen_IN();
		Display_GB2312_String_IN(1,24,"识别成功");
//		Display_GB2312_String_IN(3,0," 欢迎回来");
		//LOCK_CONTROL=1;
		delayMs(3000);
		return 1;
	}
	else if(searchnum==0)
	{
		R_LED=0x00;
		G_LED=0xff;
		B_LED=0xff;
		Clear_Screen_IN();
		Display_GB2312_String_IN(1,24,"识别失败");
		BEEP_CONTROL = 1;
		delayMs(100);
		BEEP_CONTROL = 0;
		delayMs(100);
		BEEP_CONTROL = 1;
		delayMs(100);
		BEEP_CONTROL = 0;
		delayMs(3000);
		//LOCK_CONTROL=0;
		return 0;
	}
   return 0;

}
