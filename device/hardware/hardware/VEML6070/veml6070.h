#ifndef __VEML6070_H
#define __VEML6070_H
#include "stm32f10x_map.h"

/*******************************
函数名：VEML6070_Set
函数功能：获取温湿度数据
函数返回值：成功返回0
*******************************/
unsigned char VEML6070_Set(void);

/*******************************
函数名：VEML6070_Measure
函数功能：获取温湿度数据
函数返回值：成功返回0
*******************************/
unsigned char VEML6070_Measure(u16* Result);



#endif
