/*********************************************************************************	 
		                         IIC���ģ��ͷ�ļ�		  
*********************************************************************************/ 	
#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h" 

   	   		   
//IO��������
#define SDA_IN()  {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=8<<12;}	//PB3����ģʽ
#define SDA_OUT() {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=3<<12;} //PB3���ģʽ
//IO��������	 
#define IIC_SCL    PBout(4) //SCL
#define IIC_SDA    PBout(3) //SDA	 
#define READ_SDA   PBin(3)  //����SDA 

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź� 
u8 Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_Date);//���ֽ�д��
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);//���ֽڶ�ȡ
unsigned char Single_Read_Len(unsigned char SlaveAddress,unsigned char REG_Address,u8 len,u8* buf);//���ֽڶ�ȡ
u8 Sing_Write_ND(u8 addr, u8 reg);
u8 Sing_Read_NR(u8 addr, u8 len, u8 *buf);
#endif
















