#ifndef __PM2_5_H
#define __PM2_5_H

#include "sys.h"
#include "jpstm32_gpio.h"

//��ʼ��PM2.5������
void PM2_5_Init(void);

//��ȡ����������ֵ
void PM2_5_Measure(u8* PM25_D_H, u8* PM25_D_L);




#endif
