#include "beep.h"

void beep_init(void)
{
	//1.��ʼ���˿ڵ�ʱ��
	RCC->APB2ENR |= 1<<2;
	//2.��ʼ������
	GPIOA->CRH &= 0x0FFFFFFF;
	//3.����ģʽ
	GPIOA->CRH |= 0x30000000;
	
}
