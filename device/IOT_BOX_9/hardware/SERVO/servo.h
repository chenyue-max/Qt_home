#ifndef __SERVO_H__
#define __SERVO_H__

#include "sys.h"

void servo_init(u16 arr, u16 psc);

//开
void servo_on(void);

//关
void servo_off(void);

#endif



