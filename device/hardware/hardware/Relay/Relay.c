#include "Relay.h"

void Relay_Gpio_Init()
{
	RCC->APB2ENR |= 1<<2;
	GPIOA->CRL &= 0XFF00FFFF;
	GPIOA->CRL |= 0X00330000;
}

