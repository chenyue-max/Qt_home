#include "bh1750.h"
#include "myiic.h"
#include "jpstm32_sysclk.h"

/*
IIC通信，器件地址0xB8
计算公式：测试值/(1.2*透光率*高精度调制值)
*/

#define BH1750_ADDR 0xB8 //器件地址
#define BH1750_PWOFF 0x00 //断电
#define BH1750_PWON 0x01 //通电
#define BH1750_RESET 0x07 //复位
#define BH1750_H_RE_MODE2 0x11//设置高精度调制值，解析度0.5
#define BH1750_CMT_H 0x42 //设置透光率为100%。设置寄存器高8位
#define BH1750_CNT_L 0x65 //设置透光率为100%。设置寄存器低8位


void bh1750_init(void)
{
	Sing_Write_ND(BH1750_ADDR, BH1750_PWON);//设备通电
	Sing_Write_ND(BH1750_ADDR, BH1750_RESET);
	Sing_Write_ND(BH1750_ADDR, BH1750_CMT_H);
	Sing_Write_ND(BH1750_ADDR, BH1750_CNT_L);
	Sing_Write_ND(BH1750_ADDR, BH1750_H_RE_MODE2);
}
unsigned char bh1750_measure(float* Result)
{
	unsigned char temp[2] = {0};
	u16 ST = 0;
	if(Sing_Read_NR(BH1750_ADDR, 2, temp))
	{
		ST = (temp[0]<<8)|temp[1];
		*Result = (u16)ST/0.6;
	}else{
		*Result = 0;
		return 1;
	}
	return 0;
}


