/*************************************************************
 * File name: jpstm32_sysclk.h
 * Author: Duke An
 * Version: 0.1
 * Date: 201510
 * Description: ϵͳʱ�Ӳ���ͷ�ļ�
 * Copyright @ 2013 by Briup Technology,Inc. All rights Reserved.
 *************************************************************/
#ifndef __JPSTM32_SYSCLK_H__
#define __JPSTM32_SYSCLK_H__
 
#include "jpstm32_common.h"

 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	clk_init
 * Description: ��ʼ��ϵͳʱ��
 * Input: 
 *	>PLL, ��Ƶ
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
extern void sysclkInit(u8 pll);
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	_delay_init
 * Description: 
 *	>��ʱ���ܳ�ʼ��,��ʹ��ucos��ʱ��,
 *	>�˺������ʼ��ucos��ʱ�ӽ���
 * Input: 
 *	>SYSCLK ϵͳʱ��Ƶ��,�˿�ָ���Ǳ�Ƶ֮���Ƶ��,����Ƶ
 *	 ��ǰϵͳ��Ӧ����72 ��ʾ72MHz
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void delayInit(u8 SYSCLK);
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	_delay_us
 * Description: 
 *	>΢�뼶��ʱ����
 * Input: 
 *	>��ʱ��΢����
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void delayUs(u32 nus);
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	_delay_ms
 * Description: 
 *	>���뼶��ʱ����
 * Input: 
 *	>��ʱ�ĺ����� 
 *	>ע��nms�ķ�Χ SysTick->LOADΪ24λ�Ĵ���
 *	>����,�����ʱΪ: nms<=0xffffff*8*1000/SYSCLK 
 *	>SYSCLK��λΪHz,nms��λΪms ��72M������,nms<=1864 
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void delayMs(u16 nms);
#endif
