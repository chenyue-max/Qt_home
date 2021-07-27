/*******************************************************
器件型号：5V有源蜂鸣器
通信方式：IO控制 与单片机的PA15引脚相连接
文件功能：
*******************************************************/
#include "beep.h"
#include "jpstm32_gpio.h"

void Beep_Init()
{
	RCC->APB2ENR |= 1<<2;//使能GPIOA时钟
	GPIOA->CRH &= 0X0FFFFFFF;
	GPIOA->CRH |= 0X30000000;
	BEEP_CONTROL=0;
}

