#ifndef _SECURITY_WINDOWS_H
#define _SECURITY_WINDOWS_H

#include "sys.h"
#include "jpstm32_gpio.h"

#define WARN_RING				PBxOut(8)	//报警器
#define WARN_LED				PBxOut(9)	//报警LED
#define PHOTO_SWITCH		PBxIn(0)	//光电开关
#define RELATIVE_SWITCH	PBxIn(1)	//对射开关

void Security_Windows_GPIO_Init(void);








#endif
