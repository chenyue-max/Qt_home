
//briupSPI.h
//���������Ͷ���SPI��ؽӿ�
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


//SPI��ʼ�������ӿ�
void briupSpiInit(void);

//SPI�����շ��ӿ�
u8	briupSpiWR(	u8 data);

//SPI�ٶ����ýӿ�
void briupSpiSpeedSet( u8 speed);

#endif

