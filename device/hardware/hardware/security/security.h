#ifndef _SECURITY_H_
#define _SECURITY_H_

#include "sys.h"
#include "jpstm32_gpio.h"


#define Fire_Measure					PBxIn(0)			//�����
#define Methane_Measure				PBxIn(1)			//������
#define Smog_Measure					PBxIn(6)			//������
#define Infrared_Measure			PBxIn(7)			//���������



void Security_GPIO_Init(void);




#endif
