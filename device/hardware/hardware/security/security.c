#include "security.h"


void Security_GPIO_Init()
{
	RCC->APB2ENR |= 1<<3;//ʹ��GPIOBʱ��
	GPIOB->CRL &= 0X00FFFF00;
	GPIOB->CRL |= 0X88000088;
	GPIOB->ODR |= (1<<7)|(1<<6)|(1<<1)|(1<<0);//ʹ����������
}


