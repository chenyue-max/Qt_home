#ifndef __LOCK_H__
#define __LOCK_H__

#include "jpstm32_gpio.h"

#define LOCK PBxOut(9)

void lock_init(void);//初始化函数

#endif


