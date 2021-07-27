#ifndef __A4988_H__
#define __A4988_H__

#include "stm32f10x_map.h"
#include "sys.h"

//IO对应
#define A4988_EN 	PBout(0)
#define A4988_MS1 	PBout(1)
#define A4988_MS2 	PBout(5)
#define A4988_MS3 	PBout(6)
#define A4988_RESET PBout(7)
#define A4988_SLEEP PBout(8)
#define A4988_DIR 	PBout(13)

void tim4_tim3_init(void);
/*
	cycle 是一个tim3的脉冲周期单位us
	pulse_num 是脉冲个数，决定了步进电机的步数
	步数最大65535是因为u16的限制。
	但是因为它在滑杆上所以最远能走380
*/
void motor_control(u16 cycle, u16 pulse_num);

void a4988_init(void);

#endif

