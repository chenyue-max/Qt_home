#include "Tim.h"
#include "jpstm32_gpio.h"
/*******************************
�������ܣ���ʼ��TIM3_CH1 TIM3_CH2 
								TIM3_CH3 TIM3_CH4
����������
				arr���Զ���װֵ
				pcs��ʱ��Ԥ��Ƶ��
*******************************/
void TIM3_CH1234_Init(u32 arr, u32 psc)
{
	RCC->APB1ENR|=1<<1;		//TIM3ʱ��ʹ��
	RCC->APB1ENR|=1<<2;		//TIM4ʱ��ʹ��
	RCC->APB2ENR|=1<<3;		//ʹ��PORTBʱ��
	RCC->APB2ENR|=1<<2;		//ʹ��PORTAʱ��
	//GPIOA->CRL&=0XF0FFFFFF;											
	//GPIOA->CRL|=0X0B000000;//PA6���ù������
	GPIOB->CRL&=0XF0FFFF00;											
	GPIOB->CRL|=0X0B0000BB;//PB0 1 6���ù������
	
	TIM3->ARR=arr;				//�趨�������Զ���װֵ 
	TIM3->PSC=psc;				//Ԥ��Ƶ����Ƶϵ�� 
	
	TIM4->ARR=arr;				//�趨�������Զ���װֵ 
	TIM4->PSC=psc;				//Ԥ��Ƶ����Ƶϵ�� 
	/*****************TIM3_CH1����*****************/
	//TIM3->CCMR1|=6<<4;  	//CH1 PWM1ģʽ		 
	//TIM3->CCMR1|=1<<3; 		//CH1 Ԥװ��ʹ��	
	/*****************TIM3_CH3����*****************/
	TIM3->CCMR2|=6<<4;  	//CH3 PWM1ģʽ		 
	TIM3->CCMR2|=1<<3; 		//CH3 Ԥװ��ʹ��
	/*****************TIM3_CH4����*****************/
	TIM3->CCMR2|=6<<12;  	//CH4 PWM1ģʽ		 
	TIM3->CCMR2|=1<<11; 	//CH4 Ԥװ��ʹ��
	
	/*****************TIM4_CH1����*****************/
	TIM4->CCMR1|=6<<4;  	//CH1 PWM1ģʽ		 
	TIM4->CCMR1|=1<<3; 		//CH1 Ԥװ��ʹ��
	
	//TIM3->CCER|=0<<1;   	//CH1 �ߵ�ƽ��Ч	
	//TIM3->CCER|=1<<0;   	//CH1 ���ʹ��
	TIM3->CCER|=0<<9;   	//CH3 �ߵ�ƽ��Ч	
	TIM3->CCER|=1<<8;   	//CH3 ���ʹ��
	TIM3->CCER|=0<<13;   	//CH4 �ߵ�ƽ��Ч	
	TIM3->CCER|=1<<12;   	//CH4 ���ʹ��
	TIM4->CCER|=0<<1;   	//CH1 �ߵ�ƽ��Ч	
	TIM4->CCER|=1<<0;   	//CH1 ���ʹ��
	TIM3->CR1=0X0080;   	//ARPEʹ�� 
	TIM4->CR1=0X0080;			//ARPEʹ��
	TIM3->CR1|=1<<0;    	//ʹ�ܶ�ʱ��3
	TIM4->CR1|=1<<0;			//ʹ�ܶ�ʱ��4
}
