#include "rgb_led.h"

void rgb_led_init(void)
{
	//开启GPIOA的时钟
	RCC->APB2ENR |= 1<<2;
	//初始化GPIOA的引脚
	GPIOA->CRH &= 0xFFF00FF0;
	GPIOA->CRH |= 0x00033003;
	LED_R = 1;
	LED_G = 1;
	LED_B = 1;
}

