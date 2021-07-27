#ifndef _SECURITY_H_
#define _SECURITY_H_

#include "sys.h"
#include "jpstm32_gpio.h"


#define Fire_Measure					PBxIn(0)			//»ğ¹â¼ì²â
#define Methane_Measure				PBxIn(1)			//¼×Íé¼ì²â
#define Smog_Measure					PBxIn(6)			//ÑÌÎí¼ì²â
#define Infrared_Measure			PBxIn(7)			//ÈËÌåºìÍâ¼ì²â



void Security_GPIO_Init(void);




#endif
