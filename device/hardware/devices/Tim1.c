//��ʱ��1����������

#include "Tim1.h"
#include "heart.h"
//��������ʼ��
void TIM1_Init(u16 arr,u16 psc)  
{
   RCC->APB2ENR |= 1<<11;
   TIM1->ARR = arr;
   TIM1->PSC = psc-1;
   TIM1->DIER = 1<<0;
   TIM1->CR1 |= 0x01;
   MY_NVIC_Init(2,2,TIM1_UP_IRQChannel,2);
   
}

void TIM1_UP_IRQHandler(void)
{
   TIM1->CR1 &= ~(0x01);
   if(TIM1->SR&0x0001)
   {
      //����������
	// heart_up();

   }
   TIM1->SR = ~(1<<0);
   //�����ж�
   TIM1->CR1 |= 0x01;
}


