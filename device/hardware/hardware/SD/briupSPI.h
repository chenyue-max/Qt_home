
//briupSPI.h
//用于声明和定义SPI相关接口
#ifndef __SPI_H__
#define __SPI_H__

#include "jpstm32_gpio.h"
#include "jpstm32_nvic.h"
#include "jpstm32_sysclk.h"
#include "sys.h"

#define	SPI_CLK_DIV_2		0
#define	SPI_CLK_DIV_4		1
#define	SPI_CLK_DIV_8		2
#define	SPI_CLK_DIV_16		3
#define	SPI_CLK_DIV_32		4
#define	SPI_CLK_DIV_64		5
#define	SPI_CLK_DIV_128		6
#define	SPI_CLK_DIV_256		7


//SPI初始化函数接口
void briupSpiInit(void);

//SPI数据收发接口
u8	briupSpiWR(	u8 data);

//SPI速度设置接口
void briupSpiSpeedSet( u8 speed);

#endif

