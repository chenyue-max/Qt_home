/*******************************************************
器件型号：---------
通信方式：串口
文件功能：获取二氧化碳浓度数据
获取二氧化碳数据（被动式）数据帧：
	0X42 0X4D 0XE3 0X00 0X00 0X01 0X72
*******************************************************/
#include "CO2.h"

extern volatile u8 UsartR_Finished;
extern u8 Usart3Buffer[16];
unsigned char CO2_R_COM[7]={0X42,0X4D,0XE3,0X00,0X00,0X01,0X72};

void CO2_Measure(u8* CO2_Value_H, u8* CO2_Value_L)
{
	Usart3_send(7,CO2_R_COM);//发送获取数据指令
	while(!UsartR_Finished);
	*CO2_Value_H = Usart3Buffer[4];
	*CO2_Value_L = Usart3Buffer[5];
}

void CO2_Init()
{
	usart3_init(36,9600);
}


