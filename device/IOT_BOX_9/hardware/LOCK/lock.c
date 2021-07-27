#include "lock.h"

void lock_init(void)
{
	//端口初始化
	RCC->APB2ENR |= 1<<3;
	//引脚初始化
	GPIOB->CRH &= 0xFFFFFF0F;
	//引脚模式设置 推挽输出
	GPIOB->CRH |= 0x00000030;
}

