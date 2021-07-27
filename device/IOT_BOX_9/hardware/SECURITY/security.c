#include "security.h"

void security_gpio_init(void)
{
	RCC->APB2ENR |= 1<<3;//开启B的时钟
	GPIOB->CRL &= 0x00FFFF00;
	GPIOB->CRL |= 0x88000088;
	GPIOB->ODR |= (1<<7)|(1<<6)|(1<<1)|(1<<0);

}
