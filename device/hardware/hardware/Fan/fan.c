#include "fan.h"

void Fan_Gpio_Init()
{
	RCC->APB2ENR |= 1<<2;
	GPIOA->CRL &= 0XF0FFFFFF;
	GPIOA->CRL |= 0X03000000;
}

