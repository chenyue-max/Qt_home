#ifndef _LOCK_H_
#define _LOCK_H_

#include "sys.h"
#include "jpstm32_gpio.h"
#include "jpstm32_sysclk.h"

#define LOCK_CONTROL			PBxOut(9)				//�������������

void Lock_Init(void);




#endif
