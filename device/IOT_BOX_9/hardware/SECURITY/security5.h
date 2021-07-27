#ifndef __SECURITY5_H__
#define __SECURITY5_H__

#include "sys.h"
#include "jpstm32_gpio.h"

#define WARN_BEEP PBxOut(8)
#define WARN_LED PBxOut(9)

#define PHOTO_SWITCH PBxIn(0)
#define RELATIVE_SWITCH PBxIn(1)

void security5_init(void);

#endif


