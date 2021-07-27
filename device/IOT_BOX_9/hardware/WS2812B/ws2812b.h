//这是炫彩LED的驱动文件
//ws2812b
#ifndef __WS2812B_H__
#define __WS2812B_H__

#include "stm32f10x_map.h"

#define X_LEN 4
#define Y_LEN 4 //LED的矩阵长度

//初始化函数
void ws2812b_init(void);
//使能函数
void ws2812b_en(void);
//控制函数
/*
根据起始点坐标点亮LED灯
x , y 
len。从这个x,y开始算起要点亮的个数
RGB_VALUE bit0-7 蓝色。 bit8-15绿色 bit16-23红色
mode 模式
*/
void ws2812b_pixel_en(u8 x, u8 y, u8 len, u32* RGB_Value, u8 mode);

//熄灭所有的灯
void ws2812b_clear(void);
#endif



