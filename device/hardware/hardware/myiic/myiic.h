/*********************************************************************************	 
		                         IIC软件模拟头文件		  
*********************************************************************************/ 	
#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h" 

   	   		   
//IO方向设置
#define SDA_IN()  {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=8<<12;}	//PB3输入模式
#define SDA_OUT() {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=3<<12;} //PB3输出模式
//IO操作函数	 
#define IIC_SCL    PBout(4) //SCL
#define IIC_SDA    PBout(3) //SDA	 
#define READ_SDA   PBin(3)  //输入SDA 

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号 
u8 Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_Date);//单字节写入
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);//单字节读取
unsigned char Single_Read_Len(unsigned char SlaveAddress,unsigned char REG_Address,u8 len,u8* buf);//多字节读取
u8 Sing_Write_ND(u8 addr, u8 reg);
u8 Sing_Read_NR(u8 addr, u8 len, u8 *buf);
#endif
















