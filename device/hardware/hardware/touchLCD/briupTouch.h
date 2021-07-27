/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * File name: jpstm32_touch.h
 * Author: Duke An
 * Version: 0.1
 * Date: 2014-06-17
 * Description: 触摸屏驱动头文件
 * Copyright @ 2013 by Briup Technology,Inc. All rights Reserved.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __JPSTM32_TOUCH_H__
#define __JPSTM32_TOUCH_H__


#include "briupLCD.h"

#define TP_DEBUG_ENABLE	1

#define TP_PRES_DOWN 0x80  //触屏被按下	  
#define TP_CATH_PRES 0x40  //有按键按下了 

//触摸屏引脚定义
#define TP_PEN			((GPIOF->IDR & (1<<10))>>10)	//按下检测
#define TP_OUT			((GPIOF->IDR & (1<<8)) >> 8)	//主机输入
#define	TP_IN_H()		(GPIOF->ODR |= 1<<9)	//主机输出
#define	TP_IN_L()		(GPIOF->ODR &= ~(1<<9))	//主机输出
#define	TP_CLK_H()		(GPIOB->ODR |= 1<<1)	//时钟输出
#define	TP_CLK_L()		(GPIOB->ODR &= ~(1<<1))	//时钟输出
#define	TP_CS_H()		(GPIOB->ODR |= 1<<2)	//片选
#define	TP_CS_L()		(GPIOB->ODR &= ~(1<<2))	//片选

typedef struct{
	u8 	(*init)(void);
	u8	(*scan)(u8);
	u8 	(*adjust)(void);
	//上一次坐标
	u16		lastX;
	u16		lastY;
	//当前坐标
	u16		currX;
	u16		currY;
	//屏幕是否被按下，按下 1 松开 0
	u8		penStat;
	float			xfac;
	float 		yfac;
	short			xoff;
	short			yoff;
	PenDirect direct;
	u8				cmdRdx;//X坐标读取命令
	u8				cmdRdy;//Y坐标读取命令
}TouchTpyDef;


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	tp_spiWbyte
 * Description: 向触摸屏写入一个字节
 * Input: NULL
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void tp_spiWbyte(u8 byte);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	tp_readAD
 * Description: 读取AD转换的值
 * Input: 获取AD值的命令
 * Output: NULL
 * Return: 返回读到的AD值
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
u16 tp_readAD(u8 cmd);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	tp_readXorY
 * Description: 带滤波的读取x或y的值
 * Input: 获取x或y值的命令
 * Output: NULL
 * Return: 返回读到的值
 * Others: 连续读取N次对这些数据进行排序，去掉最大和最小值
 *				 剩下的数据区平均值
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
u16 tp_readXorY(u8 cmd);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	tp_readXandY
 * Description: 读取x与y的值
 * Input: 获取保存x y值的变量
 * Output: NULL
 * Return: 返回0成功 否则失败
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
u8 tp_readXandY(u16* x, u16* y);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	tp_readXandY2
 * Description: 二次滤波 读取x与y的值
 * Input: 获取保存x y值的变量
 * Output: NULL
 * Return: 返回0成功 否则失败
 * Others: 连续2次读取触摸屏IC,且这两次的偏差不能超过
 *  			 ERR_RANGE,满足条件,则认为读数正确,否则读数错误
 *		     该函数能大大提高准确度
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
u8 tp_readXandY2(u16* x, u16* y);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	tp_drawAdjustPoint
 * Description: 绘制屏幕校准点
 * Input: 绘制坐标， 颜色
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void tp_drawAdjustPoint(u16 x, u16 y, u16 color);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	tp_scan(u8 tp)
 * Description: 搜索屏幕是否有按键按下
 * Input:  tp: 1 屏幕坐标，0 物理坐标
 * Output: NULL
 * Return: 当前屏幕状态 0 没有按下 1 有按下
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
u8 tp_scan(u8 tp);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	tp_init
 * Description: 初始化触摸屏
 * Input:  NULL
 * Output: NULL
 * Return: 成功返回0 否则返回非0
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
u8 tp_init(void);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	tp_adjust
 * Description: 屏幕校准
 * Input:  NULL
 * Output: NULL
 * Return: 成功返回0 否则返回非0
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
u8 tp_adjust(void);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	tp_showAdjustInfo
 * Description: 打印校准信息
 * Input:  NULL
 * Output: NULL
 * Return: 成功返回0 否则返回非0
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
u8 tp_printAdjustInfo(u16 pos[][2], u16 fac);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	tp_screenTrack
 * Description: 屏幕操作跟踪
 * Input:  NULL
 * Output: NULL
 * Return: 
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void tp_screenTrack(void);

//获取当前按键坐标
u8	tp_getXandY(u16* x, u16* y);

void drawToolPad(void);
#endif










