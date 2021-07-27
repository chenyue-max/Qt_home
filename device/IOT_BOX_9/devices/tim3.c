#include "tim3.h"
#include "briuplcd.h"

u16 len_x = 0;
u16 len_y = 0;
u8 len = 50;

//arr:自动重装载值
//psc:时钟分频系数
void tim3_init(u16 arr, u16 psc)
{
	RCC->APB1ENR |= 1<<1;//开启TIM3的时钟
	TIM3->ARR = arr; //设定计数的重装载值
	TIM3->PSC = psc;//设置预分频数
	TIM3->DIER |= 1<<0; //允许中断更新
	TIM3->CR1 |= 0x01;//使能定时器3
	//开启中断
	MY_NVIC_Init(1,3,TIM3_IRQChannel,2);
}

void TIM3_IRQHandler(void)
{
	if(TIM3->SR & 0x0001)
	{
		briupLcdFastDrawDirection(len_x,len_x+len, len_y, len_y+len,BLUE|RED,1);
		len_x+=10;
		if(len_x > 470)
		{
			len_x = 0;
			len_y+=10;
		}
		if(len_y >310)
		{
			len_x = 0;
			len_y = 0;
			briupLcdClear(BLACK);
		}
	}
	
	TIM3->SR &= ~(1<<0);
}


void tim1_init(u16 arr, u16 psc)
{
	RCC->APB2ENR |= 1<<11 | 1<<0;
	RCC->APB2ENR |= 1<<2;
	GPIOA->CRH &= 0xFFFFFFF0;//初始化A8
	GPIOA->CRH |= 0x0000000B;//A8复用输出
	TIM1->ARR = arr;
	TIM1->PSC = psc;

	TIM1->CCMR1 |= 7<<4;//PWM2模式

	TIM1->CCMR1 |= 1<<3;//CH1预装载值使能
	TIM1->CCER |= 1<<0;//OC1输出使能
	TIM1->BDTR |= 1<<15;//MOE主输出使能
	
	TIM1->CR1 |= 0x0080;
	TIM1->CR1|=0x01;//使能
}



