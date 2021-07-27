#include "tp4115.h"
#include "Tim.h"

void tp4115_init(void)
{
	TIM3_CH1234_Init(255, 72-1);
	tp4115_change(0,0,0,0);
}

void tp4115_change(u8 L1, u8 L2, u8 L3, u8 L4)
{
	TIM3->CCR1 = L1;
	TIM4->CCR1 = L2;
	TIM3->CCR3 = L3;
	TIM3->CCR4 = L4;
}



