//这是蜂鸣器的驱动文件头文件
#ifndef __BEEP_H__
#define __BEEP_H__

#include "jpstm32_gpio.h"

#define BEEP PAxOut(15)

//初始化函数
void beep_init(void);

#endif



