#include "rgb_led.h"

void RGB_LED_Init()
{
	RCC->APB2ENR|=1<<2;//ʹ��PORTAʱ��
	GPIOA->CRH &= 0XFFF00FF0;
	GPIOA->CRH |= 0X00033003;//PA8 11 12�������
	R_LED = 1;
	G_LED = 1;
	B_LED = 1;
}

