/*******************************************************
器件型号：VEMl6070
通信方式：IIC
文件功能：获取紫外线强度数据
器件地址：0X70
附：紫外线强度对照表（参数选择为Rset=270KΩ(硬件焊接) IT=4t）
数值											等级
0~2240				 						 低
2241~4482									 中等
4483~5976									 高
5977~8216                  非常高
>8217											 火星上，别看了，保命要紧
*******************************************************/
#include "myiic.h"
#include "veml6070.h"

#define VEML6070_ADDR	0X70	//器件地址
#define VEML6070_DH		0X73	//读温度
#define VEML6070_DL		0X71	//读湿度
/*******************************
函数名：VEML6070_Set
函数功能：获取紫外线数据
函数返回值：成功返回0			 
*******************************/
unsigned char VEML6070_Set(void)
{
	IIC_Start();
  IIC_Send_Byte(0X70);
  if (IIC_Wait_Ack()) 
		{
      IIC_Stop();
      return 1;
		}
	IIC_Send_Byte(0X0E);//此处模式配置，关闭ACK功能 IT配置为4T
	if (IIC_Wait_Ack()) 
		{
      IIC_Stop();
      return 1;
		}
	IIC_Stop();
	return  0;
}
/*******************************
函数名：VEML6070_Measure
函数功能：获取紫外线强度
函数返回值：成功返回0
*******************************/
unsigned char VEML6070_Measure(u16* Result)
{
	u8 tempH,tempL;
	/*********获取高8位数据*********/
	IIC_Start();
  IIC_Send_Byte(0X73);
  if (IIC_Wait_Ack()) 
		{
      IIC_Stop();
      return 1;
		}
	tempH=IIC_Read_Byte(1);//读取总线数据
	IIC_Stop();
	/*********获取低8位数据*********/
	IIC_Start();
  IIC_Send_Byte(0X71);
  if (IIC_Wait_Ack()) 
		{
      IIC_Stop();
      return 1;
		}
	tempL=IIC_Read_Byte(1);//读取总线数据
	IIC_Stop();
	*Result = (tempH<<8)|tempL;
	return 0;
}
