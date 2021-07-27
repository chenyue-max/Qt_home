#ifndef _SERVO_H_
#define _SERVO_H_

#include "sys.h"


void Servo_Init(u16 arr, u16 psc);
//闸机打开
void Servo_ON(void);
//闸机关闭
void Servo_OFF(void);








#endif
