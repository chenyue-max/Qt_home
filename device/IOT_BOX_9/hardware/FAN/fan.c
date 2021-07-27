#include "fan.h"


void fan_init(void)
{
	RCC->APB2ENR |= 1<<2;
	GPIOA->CRL &= 0xF0FFFFFF;
	GPIOA->CRL |= 0x03000000;	
}


