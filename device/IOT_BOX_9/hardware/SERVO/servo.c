#include "servo.h"

void servo_init(u16 arr, u16 psc)
{
	RCC->APB2ENR |= 1<<3;
	RCC->APB2ENR |= 1<<0;//使能AFIO
	GPIOB->CRH &= 0xFFFFF0FF;
	GPIOB->CRH |= 0x00000B00;//复用推完
	AFIO->MAPR &= ~(0x03<<8);
	AFIO->MAPR |= 2<<8;//将定时器2的通道3重新映射到B10
	
	RCC->APB1ENR |= 1<<0; //定时器2时钟使能
	TIM2->PSC = psc;//预分频的设置
	TIM2->ARR = arr;//自动重装载值
	TIM2->CCMR2 |= 7<<4;//通道3的PWM2模式
	TIM2->CCMR2 |= 1<<3;//通道3预装载使能
	TIM2->CCER|=1<<8;	
	TIM2->CR1 = 0x0080;//使能ARPE
	TIM2->CR1 |= 0x01;//使能定时器2

	TIM2->CCR3 = 18800;//默认关闭舵机
}

//开
void servo_on(void)
{
	TIM2->CCR3 = 19380;//打开	
}

//关
void servo_off(void)
{
	TIM2->CCR3 = 17700;//关闭
}



