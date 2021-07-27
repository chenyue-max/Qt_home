//briupSPI.c
//SPI1的接口实现文件

#include "briupSPI.h"

//SPI初始化函数接口
void briupSpiInit(void)
{
	//1.开启GPIOA与SPI1的外设时钟
	RCC->APB2ENR |= 1<<2 | 1<<12;
	
	//2.配置PA5(SPI1_SCK)
	//		PA7(SPI1_MOSI)为推挽复用输出
	//		PA6(SPI1_MISO)为带上拉的输入
	GPIOA->CRL &= 0x000fffff;
	//0xb	0b1011		0x8		0b1000
	GPIOA->CRL |= 0xB8B00000;
	
	GPIOA->ODR |= 0x07 << 5;
	
	//3.SPI配置	SPI1->CR1
	SPI1->CR1 = 0x0327;
	SPI1->CR1 |= 1<<6;
	briupSpiWR( 0xff);
}

//SPI数据收发接口
u8	briupSpiWR(	u8 data)
{
	while( !( SPI1->SR & 0x02));
	SPI1->DR = data;
	while( !( SPI1->SR & 0x01));
	return SPI1->DR;
}

//SPI速度设置接口
void briupSpiSpeedSet( u8 speed)
{
	speed &= 0x07;
	while( SPI1->SR & (1<<7));
	SPI1->CR1 &= ~(0x07 << 3);
	SPI1->CR1 |= speed << 3;
	SPI1->CR1 |= 1<<6;
}

