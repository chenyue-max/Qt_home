#include "vml6070.h"
#include "myiic.h"
/*
IIC的协议
器件地址 0x70
紫外线的对照表
0~2240       低
2241~4482    中等
4483~5976    高
5977~8216    非常高
>8216
*/
#define VML6070_ADDR 0x70
#define VML6070_DH 0x73
#define VML6070_DL 0x71


unsigned char vml6070_measure(u16* Result)
{
	u8 tempH, tempL;
	//获取高8位数据
	IIC_Start();
	IIC_Send_Byte(VML6070_DH);
	if(IIC_Wait_Ack())
	{
		IIC_Stop();
		return 1;
	}
	tempH = IIC_Read_Byte(1);//获取总线数据
	IIC_Stop();

	IIC_Start();
	IIC_Send_Byte(VML6070_DL);
	if(IIC_Wait_Ack())
	{
		IIC_Stop();
		return 1;
	}
	tempL = IIC_Read_Byte(1);
	IIC_Stop();
	*Result = (tempH<<8)|tempL;
	return 0;
}



