#ifndef __RGB_LED_H
#define __RGB_LED_H

#include "jpstm32_gpio.h"

#define R_LED			PAxOut(8)                   //��ɫLED  00
#define G_LED			PAxOut(11)									//��ɫLED  00
#define B_LED			PAxOut(12)									//��ɫLED  00


void RGB_LED_Init(void);



#endif
