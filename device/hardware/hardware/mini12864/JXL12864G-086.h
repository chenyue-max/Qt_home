/*************************************************************
 * File name	: JXL12864G-086.h
 * Author			: Bradley_Ozing（靳彦清）
 * Version		:
 * Date				: 2016-1
 * Description: JXL12864G-086(带字库)显示屏驱动头文件
 * Copyright @ 2013 by Briup Technology,Inc. All rights Reserved.
 *
 * Includes		:
 *  > 打印 GB2312 的字符串 ----> Display_GB2312_String(u8 page,u8 column,u8 *text)
 *	>	全屏清屏		-------------->	Clear_Screen(void);
 *************************************************************/
#ifndef	__JXL12864G_086_H__
#define	__JXL12864G_086_H__

#include "jpstm32_gpio.h"
#include "jpstm32_sysclk.h"



#define Lcd_Sclk_IN			PBxOut(14) 			//接口定义:Lcd_Sclk 就是 LCD 的 SCLK
#define Lcd_Sid_IN 			PBxOut(13)				//接口定义:Lcd_Sid 就是 LCD 的 SDA
#define Lcd_RS_IN				PBxOut(12)			//接口定义:Lcd_RS 就是 LCD 的 RS,也叫“CD”
#define Lcd_CS_IN				PBxOut(15) 			//接口定义:Lcd_CS 就是 LCD 的 CS1
#define Lcd_Reset_IN		PBxOut(8)				//接口定义:Lcd_Reset 就是 LCD 的 RESET
#define Rom_IN_IN				PBxOut(6) 			//字库 IC 接口定义:Rom_IN 就是字库 IC 的 SI
#define Rom_OUT_IN			PBxIn(7)  		  //字库 IC 接口定义:Rom_OUT 就是字库 IC 的 SO
#define Rom_SCK_IN			PBxOut(4)  		//字库 IC 接口定义:Rom_SCK 就是字库 IC 的 SCK
#define Rom_CS_IN				PBxOut(5)			//字库 IC 接口定义 Rom_CS 就是字库 IC 的 CS

//=====================================================================================
//
//	入库显示屏函数声明
//
//=====================================================================================


//打印GB2312的字符串
void Display_GB2312_String_IN(u8 page,u8 column,u8 *text);
//全屏清屏
void Clear_Screen_IN(void);

//LCD模块GPIO口初始化
void Lcd_GPIO_Iint_IN(void);
//LCD 模块初始化
void Lcd_Init_IN(void);
//写指令到LCD 模块
void Transfer_Cmd_Lcd_IN(int cmd);
//写数据到 LCD 模块
void Transfer_Data_Lcd_IN(int data);
//LCD 数据地址设置
void Lcd_Address_IN(u32 page,u32 column);
//显示 128x64 点阵图像
void display_128x64_IN(u8 *dp);




//送指令到晶联讯字库 IC
void send_command_to_ROM_IN( u8 datu );
//从晶联讯字库 IC 中取汉字或字符数据（1 个字节）
static u8 get_data_from_ROM_IN(void);
//从指定地址读出数据写到液晶屏指定（page, column)座标中
void get_and_write_16x16_IN(long fontaddr,u8 page,u8 column);
//从指定地址读出数据写到液晶屏指定（page, column)座标中
void get_and_write_8x16_IN(long fontaddr,u8 page,u8 column);




#endif

