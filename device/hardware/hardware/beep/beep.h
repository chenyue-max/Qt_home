#ifndef _BEEP_H_
#define _BEEP_H_

#include "sys.h"
#include "jpstm32_gpio.h"

#define BEEP_CONTROL	PAxOut(15)				//��������������

void Beep_Init(void);



#endif
