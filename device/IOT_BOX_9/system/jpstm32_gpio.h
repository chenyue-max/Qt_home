/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * File name: jpstm32_gpio.h
 * Author: Duke An
 * Version: 0.1
 * Date: 2015-10
 * Description: 系统通用I/O接口定义
 * Copyright @ 2013 by Briup Technology,Inc. All rights Reserved.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef __JPSTM32_GPIO_H__
#define __JPSTM32_GPIO_H__

#include "jpstm32_common.h"

//引脚状态值
typedef enum{
	VAL_0=0, 	/*引脚值为低电平 逻辑0*/
	VAL_1		/*引脚值为高电平 逻辑1*/
} PIN_VAL; 
//上拉、下拉状态
typedef enum{
	PULL_DOWN = 0,	/*下拉电阻标记*/
	PULL_UP	/*上拉电阻标记*/
} PULL_STAT;

//IO功能定义
#define		O_GPPP		0x00	//0B0000	//通用推挽输出
#define		O_GPOD		0x04	//0B0100	//通用开漏输出
#define		O_AFPP		0x08	//0B1000	//复用推挽输出
#define		O_AFOD		0x0c	//0b1100	//复用开漏输出
#define		I_ANA		0x00	//0B0000	//模拟输入
#define		I_FLO		0x04	//0B0100	//浮空输入
#define		I_PULLUD	0x08	//0B1000	//上拉、下拉输入

//输出模式定义
#define		OMODE_RES			0x00	//0B00	//保留
#define		OMODE_T10MHz		0x01	//0B01	//最高10MHz输出
#define		OMODE_T02MHz		0x02	//0B10	//最高2MHz输出
#define		OMODE_T50MHz		0x03	//0B11	//最高50MHz输出

//I/O接口地址定义
#define		GPIO_BASE		(APB2PERIPH_BASE+0x0800)
#define		PORTA		0x0000
#define		PORTB		0x0400
#define		PORTC		0x0800
#define		PORTD		0x0c00
#define		PORTE		0x1000
#define		PORTF		0x1400
#define		PORTG		0x1800

//引脚定义
#define		Pin0		1<<0
#define		Pin1		1<<1
#define		Pin2		1<<2
#define		Pin3		1<<3
#define		Pin4		1<<4
#define		Pin5		1<<5
#define		Pin6		1<<6
#define		Pin7		1<<7
#define		Pin8		1<<8
#define		Pin9		1<<9
#define		PinA		1<<10
#define		PinB		1<<11
#define		PinC		1<<12
#define		PinD		1<<13
#define		PinE		1<<14
#define		PinF		1<<15

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	set_gpio_port
 * Description: 配置GPIO端口
 * Input: 
 *	>PORTx,	端口名称 x=(A B C ...)
 *	>MODE, 输出模式设置, 用于设定端口输出频率 
 *	>PINx, 需要设置的引脚 Pin0~PinF 可以进行或操作
 *	>PULL_STAT, 设置引脚是否上拉
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void gpioConfig(u32 PORTx, u32 MODE, u32 PINxs, PULL_STAT stat);


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 位带操作
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//GPIONx output
#define PAxOut(x)	_BD(GPIOA->ODR, x)	//PORTAx output
#define PBxOut(x)	_BD(GPIOB->ODR, x)	//PORTBx output
#define PCxOut(x)	_BD(GPIOC->ODR, x)	//PORTCx output
#define PDxOut(x)	_BD(GPIOD->ODR, x)	//PORTDx output
#define PExOut(x)	_BD(GPIOE->ODR, x)	//PORTEx output
#define PFxOut(x)	_BD(GPIOF->ODR, x)	//PORTFx output
#define PGxOut(x)	_BD(GPIOG->ODR, x)	//PORTGx output
//GPIONx input
#define PAxIn(x)	_BD(GPIOA->IDR, x)	//PORTAx input
#define PBxIn(x)	_BD(GPIOB->IDR, x)	//PORTBx input
#define PCxIn(x)	_BD(GPIOC->IDR, x)	//PORTCx input
#define PDxIn(x)	_BD(GPIOD->IDR, x)	//PORTDx input
#define PExIn(x)	_BD(GPIOE->IDR, x)	//PORTEx input
#define PFxIn(x)	_BD(GPIOF->IDR, x)	//PORTFx input
#define PGxIn(x)	_BD(GPIOG->IDR, x)	//PORTGx input

#endif

