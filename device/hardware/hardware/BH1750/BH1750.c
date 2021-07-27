/*******************************************************
器件型号：BH1750
通信方式：IIC
文件功能：获取光照强度数据
器件地址：0XB8
光亮度值计算公式：
	实际值=测量值/(1.2*透光率*高精度模式2调整值)
读取相对温度操作指令：0XF3(非保持主机)
*******************************************************/
#include "myiic.h"
#include "BH1750.h"
#include "jpstm32_sysclk.h"

#define BH1750_ADDR					0XB8	//器件地址
#define BH1750_PWOFF				0X00	//断电
#define BH1750_PWON					0X01	//通电
#define BH1750_RESET				0X07	//复位数字寄存器中的值
#define BH1750_H_RE_MOD2		0X11 	//高精度模式2 解析度为0.5
#define BH1750_CMT_H				0X42  //设置透光率为100% 设置寄存器高8位
#define BH1750_CMT_L				0X65	//设置透光率为100% 设置寄存器低8位

/*******************************
函数名：BH1750_Init
函数功能：初始化BH1750
函数返回值：成功返回0
*******************************/
void BH1750_Init(void)
{
	Sing_Write_ND(BH1750_ADDR, BH1750_PWON);		//通电
	Sing_Write_ND(BH1750_ADDR, BH1750_RESET);		//复位
	Sing_Write_ND(BH1750_ADDR, BH1750_CMT_H);	
	Sing_Write_ND(BH1750_ADDR, BH1750_CMT_L);			//设置透光率为100%
	Sing_Write_ND(BH1750_ADDR, BH1750_H_RE_MOD2);	//设置为高精度模式
}	
/*******************************
函数名：BH1750_Init
函数功能：初始化BH1750
函数返回值：成功返回0
*******************************/
void BH1750_Start(void)
{
	Sing_Write_ND(BH1750_ADDR, BH1750_PWON);		//通电
	Sing_Write_ND(BH1750_ADDR, BH1750_RESET);		//复位
	Sing_Write_ND(BH1750_ADDR, BH1750_CMT_H);	
	Sing_Write_ND(BH1750_ADDR, BH1750_CMT_L);			//设置透光率为100%
	Sing_Write_ND(BH1750_ADDR, BH1750_H_RE_MOD2);	//设置为高精度模式
}	

/*******************************
函数名：BH1750_Measure
函数功能：获取一次BH1750的测量值
函数返回值：成功返回0
注意：每次读取光照强度数据至少要间隔120ms
			在高精度模式下传感器转换一次数据需要至少120ms时间
*******************************/
unsigned char BH1750_Measure(float* Result)
{
	unsigned char temp[2]={0};
	u16 ST = 0;
	if(Sing_Read_NR(BH1750_ADDR, 2, temp))
	 {
		ST = (temp[0]<<8)|temp[1];
		*Result = (u16)ST / 0.6;
	 }
	else
	{
		*Result = 0;
		return 1;
	}
	return 0;
}

/*******************************
函数名：BH1750_Measure
函数功能：获取一次BH1750的原始测量值
函数返回值：成功返回0
注意：每次读取光照强度数据至少要间隔120ms
			在高精度模式下传感器转换一次数据需要至少120ms时间
*******************************/
unsigned char BH1750_Original_Measure(u16* Result)
{
	unsigned char temp[2]={0};
//	u16 ST = 0;
	if(Sing_Read_NR(BH1750_ADDR, 2, temp))
	 {
		* Result = (temp[0]<<8)|temp[1];
	 }
	else
	{
		*Result = 0;
		return 1;
	}
	return 0;
}






