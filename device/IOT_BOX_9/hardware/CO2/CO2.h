#ifndef __CO2_H
#define __CO2_H
#include "usart3.h"

void CO2_Init(void);
void CO2_Measure(u8* CO2_Value_H, u8* CO2_Value_L);




#endif
