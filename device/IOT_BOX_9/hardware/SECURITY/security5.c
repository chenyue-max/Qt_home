#include "security5.h"

void security5_init(void)
{
	RCC->APB2ENR |= 1<<3;
	GPIOB->CRL &= 0xFFFFFF00;
	GPIOB->CRH &= 0xFFFFFF00;

	GPIOB->CRL |= 0x00000088;
	GPIOB->CRH |= 0x00000033;

	GPIOB->ODR |= (1<<0)|(1<<1);
}



