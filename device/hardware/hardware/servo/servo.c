#include "servo.h"

void Servo_Init(u16 arr, u16 psc)
{
	RCC->APB2ENR |= 1<<3;
	RCC->APB2ENR |= 1<<0;//ʹ��AFIOʱ��
	GPIOB->CRH &= 0XFFFFF0FF;
	GPIOB->CRH |= 0X00000B00;//���ù����������
	AFIO->MAPR &=~(0X03<<8);
	AFIO->MAPR |= 2<<8;//��TIM2_CH3��ӳ����PB10
	
	/**********�����Ƕ�ʱ���ĳ�ʼ��**************/
	RCC->APB1ENR|=1<<0;			//TIM2ʱ��ʹ��
	TIM2->ARR=arr;					//�趨�������Զ���װֵ
	TIM2->PSC=psc;					//Ԥ��Ƶ������Ƶ
	
	TIM2->CCMR2|=7<<4;			//CH3 PWM2ģʽ
	TIM2->CCMR2|=1<<3;			//CH3Ԥװ��ʹ��
	TIM2->CCER|=1<<8;				//OC3���ʹ��
	TIM2->CR1=0x0080;				//ARPEʹ��
	TIM2->CR1|=0X01;				//ʹ�ܶ�ʱ��2
	TIM2->CCR3=18800;				//Ĭ���ϵ�رճ���բ��
}
//բ����
void Servo_ON(void)
{
	TIM2->CCR3=19450;//�򿪳���բ��
}
//բ���ر�
void Servo_OFF(void)
{
	TIM2->CCR3=17700;//�رճ���բ��
}

