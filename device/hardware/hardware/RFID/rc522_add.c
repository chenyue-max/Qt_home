//#include "include.h"
#include <stm32f10x_map.h>
#include <stm32f10x_nvic.h> 

#include "sys.h"
#include "lcd.h"	   

#include "rc522.h"
#include "rc522_add.h"

#include <string.h>
#include <stdio.h>
#include "led.h" 



//读卡相关数据的定义
u16  KuaiN;//表示要访问的块
u8 oprationcard,bSendID;
u8 Read_Data[16],
	 PassWd[6]={0xff,0xff,0xff,0xff,0xff,0xff},
	 WriteData[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	 RevBuffer[30],
	 MLastSelectedSnr[4],
	 NewKey[16];		       
	 
// char cardID[4];//卡号
u8 cardID[4];//卡号

u8 flag_com;   //已读到卡的标志

double temp_money=0;//卡内余额（32位有效数字？？）

u8 administrator[4]={0x34,0xb2,0x1e,0xeb};//管理员卡号
u8 datatemp[4];	 //从AT24C02读出来的卡号
	 
	 
	 
	 
	 
	 
//串口发送一个字节（8位二进制数）
#define USART_FLAG_TXE   ((u16)0x0080)
	 
void UART1_SendByte(u16 Data)
{ 
   while (!(USART1->SR & USART_FLAG_TXE));
   USART1->DR = (Data & (u16)0x01FF);	    
}
	 
	 
	 


 /*******************************************************************************
* 描  述  :  初始化所有读卡相关数据的设置
* 输  入  :  无
* 输  出  :  无
* 返  回  :  无
*******************************************************************************/
void InitAlldata(void)
{	
  LED0=1;//LED0灭
	
	flag_com=0;//已读到卡的标志
  KuaiN=0;
  oprationcard=0;
  bSendID=0;
}


 /*******************************************************************************
* 描  述  :  判断操作类型（发送卡号、读卡、写卡、修改密码 ）
* 输  入  :  0xa0,0xa1,0xa2,0xa3
* 输  出  :  无
* 返  回  :  无
*******************************************************************************/
void command_choose(u8 command)
{
//   u8 ii;
	
	InitAlldata();			//初始化所有读卡相关数据的设置
	
  switch(command)
  {
    case 0xa0://发送卡号
							oprationcard=SENDID;
							break;
		
    case 0xa1://读数据
							oprationcard=READCARD;
// 							for(ii=0;ii<6;ii++)
// 							{
// 								PassWd[ii]=RevBuffer[ii+2];//RevBuffer[]数组的第三到第八个数据表示密码
// 							} 
							KuaiN=4;//表示要操作块几（如块4：第二个扇区的第一个数据块）
							break;
			
    case 0xa2://写数据
							oprationcard=WRITECARD;
// 							for(ii=0;ii<6;ii++)
// 							{
// 								PassWd[ii]=RevBuffer[ii+2];//RevBuffer[]数组的第三到第八个数据表示密码
// 							} 
							KuaiN=4;//表示要操作块几（如块4：第二个扇区的第一个数据块）
// 							for(ii=0;ii<16;ii++)
// 							{
// 								WriteData[ii]=RevBuffer[ii+9];//要写入的16个数据
// 							}
							break;  
			
    case 0xa3://修改密码
							oprationcard=KEYCARD; 
// 							for(ii=0;ii<6;ii++)
// 							{
// 								PassWd[ii]=RevBuffer[ii+2];//RevBuffer[]数组的第三到第八个数据表示密码
// 							} 
							KuaiN=7;//表示要操作块几（如块7：第二个扇区的尾块密码A存放区）
// 							for(ii=0;ii<6;ii++)
// 							{
// 								NewKey[ii]=RevBuffer[ii+9];
// 								NewKey[ii+10]=RevBuffer[ii+9];//RevBuffer[]数组的第十到第十五个数据表示新密码
// 							}
							break;
			
    default:  break;                     
  }
}


 /*******************************************************************************
* 描  述  :  对寻卡、防冲撞、选卡、发送卡号、读卡、写卡、修改密码进行操作
             成功则LED0灯亮
* 输  入  :  无
* 输  出  :  无
* 返  回  :  无
*******************************************************************************/
void ctrlprocess(void)
{
  unsigned char ii;
  char status;
  
  PcdReset();//复位RC522
  status=PcdRequest(PICC_REQIDL,&RevBuffer[0]);//寻天线区内未进入休眠状态的卡，返回卡片类型 2字节
  if(status!=MI_OK) return ;
 
  status=PcdAnticoll(&RevBuffer[2]);//防冲撞，返回卡的序列号 4字节
  if(status!=MI_OK) return ;
	
  memcpy(MLastSelectedSnr,&RevBuffer[2],4);//从&RevBuffer[2]这个地址开始拷贝4个字节到指针起始位置MLastSelectedSnr
  status=PcdSelect(MLastSelectedSnr);//选卡
  if(status!=MI_OK) return ;
	
	
	
	//修改密码命令
  if(oprationcard==KEYCARD)
  {
    oprationcard=0;    
    status=PcdAuthState(PICC_AUTHENT1A,KuaiN,PassWd,MLastSelectedSnr);//验证A密匙
    if(status!=MI_OK) return ;
		
    status=PcdWrite(KuaiN,&NewKey[0]);//修改密码
    if(status!=MI_OK) return ;	
		
    PcdHalt();//命令卡片进入休眠状态
		LED0=0;//LED0亮			

		flag_com=1;//已读到卡的标志
  }
	
	//读卡命令（卡内余额）
  else if(oprationcard==READCARD)
  {
    oprationcard=0;
    status=PcdAuthState(PICC_AUTHENT1A,KuaiN,PassWd,MLastSelectedSnr);//验证A密匙
    if(status!=MI_OK)  return ;
    
    status=PcdRead(KuaiN,Read_Data);//从M1卡某一块读取到的数据存放在Read_Data[]数组中
    if(status!=MI_OK)  return ;
    
		for(ii=0;ii<16;ii++)UART1_SendByte(Read_Data[ii]);//将读到的数据通过串口发送给电脑	   
		
//     for(ii=0;ii<16;ii++)
// 			LCD_ShowNum(10+ii*8,180,Read_Data[ii],1,16);//显示读到的16个数据
		
    PcdHalt();//命令卡片进入休眠状态
		LED0=0;//LED0亮			

		flag_com=1;//已读到卡的标志
  }
	
	//写卡命令（卡内余额）
  else if(oprationcard==WRITECARD)
  {
    oprationcard=0;
    status=PcdAuthState(PICC_AUTHENT1A,KuaiN,PassWd,MLastSelectedSnr);//验证A密匙
    if(status!=MI_OK) return ;

    status=PcdWrite(KuaiN,&WriteData[0]);//把WriteData[]数组中的数据写到M1卡某一块中
    if(status!=MI_OK) return ;
		
		for(ii=0;ii<16;ii++)UART1_SendByte(WriteData[ii]);//将写进卡内的数据通过串口发送给电脑	   

		PcdHalt();//命令卡片进入休眠状态
		LED0=0;//LED0亮		

		flag_com=1;//已读到卡的标志		
  } 
	
	//显示卡号命令（姓名、学号、卡号）
  else if(oprationcard==SENDID)
  {
    oprationcard=0;
		
    for(ii=0;ii<4;ii++)
    {
	  	cardID[ii]=MLastSelectedSnr[ii];//cardID[]存放着4个2位的16进制数
			
// 			UART1_SendByte(MLastSelectedSnr[ii]);//将卡号（ID）通过串口发送到电脑
			printf("ID=%d\n",MLastSelectedSnr[ii]);
			
// 			LCD_ShowNum(10+ii*8,150,MLastSelectedSnr[ii],3,16);//显示ID（3位10进制数）
    }
		
		PcdHalt();//命令卡片进入休眠状态
		LED0=0;//LED0亮			

		flag_com=1;//已读到卡的标志
  }  
	
}


 /*******************************************************************************
* 描  述  :  每进入两次定时器中断（即50ms）则对操作类型重新选择（判断）
* 输  入  :  无
* 输  出  :  无
* 返  回  :  无
*******************************************************************************/
void RC522_work(void)
{  
	ctrlprocess();  //对寻卡、防冲撞、选卡、发送卡号、读卡、写卡、修改密码进行操作
}


//求10的n次方
int Mult10(int n)
{  
  int sum = 10;  
  int m;  
  if(n==0) return 1;  
  for(m=1;m<n;m++) sum*=10;  
  return sum;
}


//读卡号（存放在cardID[]数组中：4个8位的16进制数）
void Read_cardID(void)
{
	command_choose(0xa0);	//读卡号	
	RC522_work();					//描  述  :  每进入两次定时器中断（即50ms）则对操作类型重新选择（判断）
}


//读卡内余额（存放在Read_Data[]数组中）	
//temp_money=Read_overage();
double Read_overage(void)
{
	u8 ii=0;
	double overage=0;
	
	command_choose(0xa1);	//读卡信息	
	RC522_work();					//描  述  :  每进入两次定时器中断（即50ms）则对操作类型重新选择（判断）
		
	for(ii=1;ii<16;ii++)
	{
		if(Read_Data[ii] != 0)
			overage=overage+Read_Data[ii]*Mult10(ii-1); //计算整数部分
	}
	overage=overage+Read_Data[0]/10.0;							//计算小数部分
	
	return overage;
}


//写卡内余额（存放在WriteData[]数组中）	
//write_overage(temp_money);
void write_overage(double overage)
{
	u8 ii=0;
	u8 temp=0;
	
	command_choose(0xa2);	//写卡信息	
	for(ii=0;ii<16;ii++)
	{
		WriteData[ii]=0;//清零
	}
	
	for(ii=15;ii>0;ii--)
	{
		temp=(u8)(overage/Mult10(ii-1));
		WriteData[ii]=temp;
		overage=overage-temp*Mult10(ii-1);
	}
	temp=(u8)(overage*10);
	WriteData[0]=temp;
	
	RC522_work();					//描  述  :  每进入两次定时器中断（即50ms）则对操作类型重新选择（判断）
}






































/***************************************
*函数功能：显示卡的卡号，以十六进制显示
*参数：x，y 坐标
*		   p    卡号的地址
*	charcolor 字符的颜色
*	bkcolor   背景的颜色
***************************************/
void ShowID(u16 x,u16 y, u8 *p, u16 charColor, u16 bkColor)	
{
	u8 num[9];
	u8 i;

	for(i=0;i<4;i++)
	{
		num[i*2]=p[i]/16;
		num[i*2]>9?(num[i*2]+='7'):(num[i*2]+='0');
		num[i*2+1]=p[i]%16;
		num[i*2+1]>9?(num[i*2+1]+='7'):(num[i*2+1]+='0');
	}
	num[8]=0;
	
	POINT_COLOR=RED;	  
	LCD_ShowString(x,y,"The Card ID is:");	
	
 	for(i=0;i<9;i++)
	{
		LCD_ShowNum(x+16*i,y+16,num[i],2,16);
	}
}
 

// u8 ReadData(u8   addr,u8 *pKey,u8 *pSnr,u8 *dataout)
// {
// 	u8 status,k;
// 	status=0x02;
// 	k=5;
// 	
// 	do
//   {
// 		status=PcdAuthState(PICC_AUTHENT1A,addr,pKey,pSnr);
// 		k--;
// 		//printf("AuthState is wrong\n");						      
//   }while(status!=MI_OK && k>0);

// 	
// 	status=0x02;
// 	k=5;
// 	
// 	do
//   {
// 		status=PcdRead(addr,dataout);
// 		k--;
// 		//printf("ReadData is wrong\n");							      
//   }while(status!=MI_OK && k>0);
// 	
// 	return status;
// }


// u8 WriteData(u8   addr,u8 *pKey,u8 *pSnr,u8 *datain)
// {
// 	u8 status,k;
// 	status=0x02;
// 	k=5;
// 	
// 	do
//   {
// 		status=PcdAuthState(PICC_AUTHENT1A,addr,pKey,pSnr);
// 		k--;
// 		//printf("AuthState is wrong\n");						      
//   }while(status!=MI_OK && k>0);

// 	
// 	status=0x02;
// 	k=5;
// 	
// 	do
//   {
// 		status=PcdWrite(addr,datain);
// 		k--;
// 		//printf("ReadData is wrong\n");							      
//   }while(status!=MI_OK && k>0);
// 	
// 	return status;
// }


void PutNum(u16 x,u16 y, u32 n1,u8 n0, u16 charColor, u16 bkColor)
{

}


void Store(u8 *p,u8 store,u8 cash)
{

}




