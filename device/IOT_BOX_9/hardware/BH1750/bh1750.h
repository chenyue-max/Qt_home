#ifndef __BH1750_H__
#define __BH1750_H__

#include "stm32f10x_map.h"

void bh1750_init(void);
unsigned char bh1750_measure(float* Result);

#endif

