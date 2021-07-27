#ifndef __RELAY_H__
#define __RELAY_H__

#include "jpstm32_gpio.h"

#define Relay1_Set PAxOut(5)
#define Relay2_Set PAxOut(4)

void relay_init(void);

#endif


