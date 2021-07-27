#ifndef __FAN_H__
#define __FAN_H__

#include "jpstm32_gpio.h"

#define Fan_Set PAxOut(6)

void fan_init(void);

#endif


