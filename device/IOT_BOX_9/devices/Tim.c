#include "Tim.h"
#include "jpstm32_gpio.h"
/*******************************
函数功能：初始化TIM3_CH1 TIM3_CH2 
								TIM3_CH3 TIM3_CH4
函数参数：
				arr：自动重装值
				pcs：时钟预分频数
*******************************/
void TIM3_CH1234_Init(u32 arr, u32 psc)
{
	RCC->APB1ENR|=1<<1;		//TIM3时钟使能
	RCC->APB1ENR|=1<<2;		//TIM4时钟使能
	RCC->APB2ENR|=1<<3;		//使能PORTB时钟
	RCC->APB2ENR|=1<<2;		//使能PORTA时钟
	//GPIOA->CRL&=0XF0FFFFFF;											
	//GPIOA->CRL|=0X0B000000;//PA6复用功能输出
	GPIOB->CRL&=0XF0FFFF00;											
	GPIOB->CRL|=0X0B0000BB;//PB0 1 6复用功能输出
	
	TIM3->ARR=arr;				//设定计数器自动重装值 
	TIM3->PSC=psc;				//预分频器分频系数 
	
	TIM4->ARR=arr;				//设定计数器自动重装值 
	TIM4->PSC=psc;				//预分频器分频系数 
	/*****************TIM3_CH1配置*****************/
	//TIM3->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	//TIM3->CCMR1|=1<<3; 		//CH1 预装载使能	
	/*****************TIM3_CH3配置*****************/
	TIM3->CCMR2|=6<<4;  	//CH3 PWM1模式		 
	TIM3->CCMR2|=1<<3; 		//CH3 预装载使能
	/*****************TIM3_CH4配置*****************/
	TIM3->CCMR2|=6<<12;  	//CH4 PWM1模式		 
	TIM3->CCMR2|=1<<11; 	//CH4 预装载使能
	
	/*****************TIM4_CH1配置*****************/
	TIM4->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	TIM4->CCMR1|=1<<3; 		//CH1 预装载使能
	
	//TIM3->CCER|=0<<1;   	//CH1 高电平有效	
	//TIM3->CCER|=1<<0;   	//CH1 输出使能
	TIM3->CCER|=0<<9;   	//CH3 高电平有效	
	TIM3->CCER|=1<<8;   	//CH3 输出使能
	TIM3->CCER|=0<<13;   	//CH4 高电平有效	
	TIM3->CCER|=1<<12;   	//CH4 输出使能
	TIM4->CCER|=0<<1;   	//CH1 高电平有效	
	TIM4->CCER|=1<<0;   	//CH1 输出使能
	TIM3->CR1=0X0080;   	//ARPE使能 
	TIM4->CR1=0X0080;			//ARPE使能
	TIM3->CR1|=1<<0;    	//使能定时器3
	TIM4->CR1|=1<<0;			//使能定时器4
}
