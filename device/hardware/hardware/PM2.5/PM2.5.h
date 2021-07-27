#ifndef __PM2_5_H
#define __PM2_5_H

#include "sys.h"
#include "jpstm32_gpio.h"

//初始化PM2.5传感器
void PM2_5_Init(void);

//获取传感器数据值
void PM2_5_Measure(u8* PM25_D_H, u8* PM25_D_L);




#endif
