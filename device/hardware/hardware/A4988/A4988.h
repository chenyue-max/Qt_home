#ifndef __A4988_H
#define __A4988_H

#include "stm32f10x_map.h"
#include "sys.h"
//IO操作函数	 
#define A4988_EN	  	PBout(0) 
#define A4988_MS1    	PBout(1) 	 
#define A4988_MS2	  	PBout(5) 
#define A4988_MS3    	PBout(6) 
#define A4988_RESET	  PBout(7) 
#define A4988_SLEEP   PBout(8) 
#define A4988_DIR	  	PBout(13) 



/******************************************
函数名：TIM4_TIM3_Init
函数功能：通过配置TIM4 TIM3为主从模式实现
					准确脉冲个数输出
					此方式多用于步进电机与伺服电机驱动
*******************************************/
void  TIM4_TIM3_Init(void);

/*********************************************************
名称：Motor_Control(u16 cycle, u16 pulse_num)
说明：生成指定个数脉冲，每个脉冲周期为cycle微秒，脉冲个数生成的个数
      和单脉冲高电平时间有关系，脉冲个数就由高电平时间来确定
参数cycle：为TIM3一个脉冲周期,单位(us)
参数pulse_num：为脉冲个数，决定步进电机步数
返回值：无
*********************************************************/
void Motor_Control(u16 cycle, u16 pulse_num);

/******************************************
函数名：A4988_Init
函数功能：初始化A4988步进电机驱动芯片
*******************************************/
void  A4988_Init(void);


#endif
