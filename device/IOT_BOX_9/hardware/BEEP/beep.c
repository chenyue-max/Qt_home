#include "beep.h"

void beep_init(void)
{
	//1.初始化端口的时钟
	RCC->APB2ENR |= 1<<2;
	//2.初始化引脚
	GPIOA->CRH &= 0x0FFFFFFF;
	//3.设置模式
	GPIOA->CRH |= 0x30000000;
	
}
