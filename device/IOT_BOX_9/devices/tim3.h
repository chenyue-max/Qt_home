
#ifndef __TIM3_H__
#define __TIM3_H__

#include "sys.h"

#define LED_PWM_VAL TIM1->CCR1 //PA8

void tim3_init(u16 arr, u16 psc);

void tim1_init(u16 arr, u16 psc);

#endif

