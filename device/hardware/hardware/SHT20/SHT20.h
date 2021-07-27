#ifndef __SHT20_H
#define __SHT20_H
#include "myiic.h"

/*******************************
函数名：SHT20_Measure
函数功能：获取温湿度数据
函数返回值：成功返回0
*******************************/
unsigned char SHT20_Measure(float* Temperature, float* Humidity);
/*******************************
函数名：SHT20_Original_TEMP
函数功能：获取原始温度数据
函数返回值：成功返回0
*******************************/
unsigned char SHT20_Original_TEMP(u16* Temperature);
/*******************************
函数名：SHT20_Original_HUM
函数功能：获取原始湿度数据
函数返回值：成功返回0
*******************************/
unsigned char SHT20_Original_HUM(u16* Humidity);

#endif
