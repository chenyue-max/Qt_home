#ifndef __WS2812B_H
#define __WS2812B_H

#include "stm32f10x_map.h"

#define X_LEN			8	//����LEDX����
#define Y_LEN			8 //����LEDY����
																							
void WS2812B_Init(void);
void WS2812B_EN(void);
/*********************************************
������     WS2812B_Pixel_EN
�������ܣ�������ʼ��������LED
�������: x,yΪ��ʼ�����
					len������ʼ����㿪ʼ��������Ҫ����LED�ĸ�����
					RGB_Value:��Ҫ��ʾ����ɫ bit0-7��ɫ bit8-15��ɫ bit16-23��ɫ  ff��ʾ��Ӧֵ
					mode����ʾģʽ 
*********************************************/
void WS2812B_Pixel_EN(u8 x,u8 y,u8 len,u32* RGB_Value,u8 mode);
/*********************************************
������     WS2812B_Clear
�������ܣ� Ϩ�����е�LED
*********************************************/
void WS2812B_Clear(void);
#endif
