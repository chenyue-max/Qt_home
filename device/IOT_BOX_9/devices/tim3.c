#include "tim3.h"
#include "briuplcd.h"

u16 len_x = 0;
u16 len_y = 0;
u8 len = 50;

//arr:�Զ���װ��ֵ
//psc:ʱ�ӷ�Ƶϵ��
void tim3_init(u16 arr, u16 psc)
{
	RCC->APB1ENR |= 1<<1;//����TIM3��ʱ��
	TIM3->ARR = arr; //�趨��������װ��ֵ
	TIM3->PSC = psc;//����Ԥ��Ƶ��
	TIM3->DIER |= 1<<0; //�����жϸ���
	TIM3->CR1 |= 0x01;//ʹ�ܶ�ʱ��3
	//�����ж�
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
	GPIOA->CRH &= 0xFFFFFFF0;//��ʼ��A8
	GPIOA->CRH |= 0x0000000B;//A8�������
	TIM1->ARR = arr;
	TIM1->PSC = psc;

	TIM1->CCMR1 |= 7<<4;//PWM2ģʽ

	TIM1->CCMR1 |= 1<<3;//CH1Ԥװ��ֵʹ��
	TIM1->CCER |= 1<<0;//OC1���ʹ��
	TIM1->BDTR |= 1<<15;//MOE�����ʹ��
	
	TIM1->CR1 |= 0x0080;
	TIM1->CR1|=0x01;//ʹ��
}



