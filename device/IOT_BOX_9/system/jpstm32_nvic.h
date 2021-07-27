/*************************************************************
 * File name: jpstm32_nvic.h
 * Author: Duke An
 * Version: 0.1
 * Date: 2015-10
 * Description: 系统中断设置
 * Copyright @ 2013 by Briup Technology,Inc. All rights Reserved.
 *************************************************************/
#ifndef __JPSTM32_NVIC_H__
#define __JPSTM32_NVIC_H__

#include "jpstm32_common.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	select_nvic_vector
 * Description: 设置系统NVIC向量表的存储位置
 * Input: 
 *	>NVIC_VectTab, 向量表存储位置
 *  >Offset, 偏移量
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
extern void nvicSetVector(u32 NVIC_VectTab, u32 Offset);

extern bool nvicSetEnable(u8 Channel);
extern bool nvicClearEnable(u8 Channel);
extern bool nvicSetPending(u8 Channel);
extern bool nvicClearPending(u8 Channel);
extern bool nvicGetActive(u8 Channel);
extern bool nvicSetGroup(u8 group);
extern bool nvicSetPriority(u8 Channel, u8 PreemptionPriority, u8 SubPriority);
extern vu32 nvicGetPriority(void);

extern bool nvicRegister(u8 nvic_Group, u8 nvic_PreemptionPriority, u8 nvic_SubPriority, u8 nvic_Channel);


#endif
