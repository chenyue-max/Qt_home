#ifndef __WS2812B_H
#define __WS2812B_H

#include "stm32f10x_map.h"

#define X_LEN			8	//矩阵LEDX长度
#define Y_LEN			8 //矩阵LEDY长度
																							
void WS2812B_Init(void);
void WS2812B_EN(void);
/*********************************************
函数名     WS2812B_Pixel_EN
函数功能：根据起始坐标点点亮LED
输入参数: x,y为起始坐标点
					len：以起始坐标点开始（包括）要点亮LED的个数。
					RGB_Value:将要显示的颜色 bit0-7蓝色 bit8-15绿色 bit16-23红色  ff显示对应值
					mode：显示模式 
*********************************************/
void WS2812B_Pixel_EN(u8 x,u8 y,u8 len,u32* RGB_Value,u8 mode);
/*********************************************
函数名     WS2812B_Clear
函数功能： 熄灭所有的LED
*********************************************/
void WS2812B_Clear(void);
#endif
