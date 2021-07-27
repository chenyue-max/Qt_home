/*************************************************************
 * File name: jpstm32_common.h
 * Author: Duke An
 * Version: 0.1
 * Date: 2014-10
 * Description: ϵͳͨ��ͷ�ļ������ڶ���ͨ�����ݽṹ��
 * Copyright @ 2013 by Briup Technology,Inc. All rights Reserved.
 *************************************************************/
#ifndef __COMMON_H__
#define __COMMON_H__

#include "stm32f10x_map.h"
#include "stm32f10x_nvic.h"

//ϵͳĬ���жϷ���
#define NVIC_GROUP_VAL		0

//�����������Ͷ���
typedef unsigned 	char		u8;
typedef unsigned 	short		u16;
typedef signed		char		s8;
typedef signed		short		s16;

 /* * * * * * * * * * * * * * * * * * * * * * * * * * * 
  * λ����������SRAM����ַת����λ����������ַ
	* >reg Ҫת����λ���ڵļĴ���
	* >bitn Ҫת����λ
	* 0x42000000+(A-0x40000000)*32+n*4
	* 0x22000000+(A-0x20000000)*32+n*4
  * * * * * * * * * * * * * * * * * * * * * * * * * * */
#define _BD(reg, bitn)\
	*((vu32*)(((vu32)(&reg)&0xF0000000)+0x2000000\
	+(((vu32)(&reg)&0xFFFFF)<<5) + (bitn<<2)))


#endif


