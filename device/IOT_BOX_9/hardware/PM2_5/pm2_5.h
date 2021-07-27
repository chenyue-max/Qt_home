#ifndef __PM25_H__
#define __PM25_H__

#include "sys.h"
#include "jpstm32_gpio.h"

void pm2_5_init(void);
void pm2_5_measure(u8* pm25DH, u8* pm25DL);

#endif


