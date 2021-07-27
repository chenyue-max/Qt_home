#ifndef __SECURITY_H__
#define __SECURITY_H__

#include "sys.h"
#include "jpstm32_gpio.h"

#define Fire PBxIn(0) //火光检测
#define Methane PBxIn(1) //甲烷
#define Smong PBxIn(6) //烟雾
#define Infrared PBxIn(7) //人体红外

void security_gpio_init(void);

#endif




