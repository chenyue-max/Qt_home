/*************************************************************
 * File name: jpstm32_sysclk.h
 * Author: Duke An
 * Version: 0.1
 * Date: 201510
 * Description: 系统时钟操作头文件
 * Copyright @ 2013 by Briup Technology,Inc. All rights Reserved.
 *************************************************************/
#ifndef __JPSTM32_SYSCLK_H__
#define __JPSTM32_SYSCLK_H__
 
#include "jpstm32_common.h"

 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	clk_init
 * Description: 初始化系统时钟
 * Input: 
 *	>PLL, 倍频
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
extern void sysclkInit(u8 pll);
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	_delay_init
 * Description: 
 *	>延时功能初始化,当使用ucos的时候,
 *	>此函数会初始化ucos的时钟节拍
 * Input: 
 *	>SYSCLK 系统时钟频率,此刻指的是倍频之后的频率,即主频
 *	 当前系统中应传入72 表示72MHz
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void delayInit(u8 SYSCLK);
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	_delay_us
 * Description: 
 *	>微秒级延时程序
 * Input: 
 *	>延时的微秒数
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void delayUs(u32 nus);
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	_delay_ms
 * Description: 
 *	>毫秒级延时程序
 * Input: 
 *	>延时的毫秒数 
 *	>注意nms的范围 SysTick->LOAD为24位寄存器
 *	>所以,最大延时为: nms<=0xffffff*8*1000/SYSCLK 
 *	>SYSCLK单位为Hz,nms单位为ms 对72M条件下,nms<=1864 
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void delayMs(u16 nms);
#endif
