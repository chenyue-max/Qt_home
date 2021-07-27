#ifndef _SECURITY_WINDOWS_H
#define _SECURITY_WINDOWS_H

#include "sys.h"
#include "jpstm32_gpio.h"

#define WARN_RING				PBxOut(8)	//������
#define WARN_LED				PBxOut(9)	//����LED
#define PHOTO_SWITCH		PBxIn(0)	//��翪��
#define RELATIVE_SWITCH	PBxIn(1)	//���俪��

void Security_Windows_GPIO_Init(void);








#endif
