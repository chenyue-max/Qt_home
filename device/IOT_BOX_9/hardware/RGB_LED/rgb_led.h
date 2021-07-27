/*
小的三色led灯的初始化
*/
#ifndef __RGB_LED_H__
#define __RGB_LED_H__

#include "jpstm32_gpio.h"

#define LED_R PAxOut(8)
#define LED_G PAxOut(11)
#define LED_B PAxOut(12)

//RGBLED灯的初始化
void rgb_led_init(void);

#endif




