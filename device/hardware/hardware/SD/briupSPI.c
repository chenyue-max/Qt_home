//briupSPI.c
//SPI1�Ľӿ�ʵ���ļ�

#include "briupSPI.h"

//SPI��ʼ�������ӿ�
void briupSpiInit(void)
{
	//1.����GPIOA��SPI1������ʱ��
	RCC->APB2ENR |= 1<<2 | 1<<12;
	
	//2.����PA5(SPI1_SCK)
	//		PA7(SPI1_MOSI)Ϊ���츴�����
	//		PA6(SPI1_MISO)Ϊ������������
	GPIOA->CRL &= 0x000fffff;
	//0xb	0b1011		0x8		0b1000
	GPIOA->CRL |= 0xB8B00000;
	
	GPIOA->ODR |= 0x07 << 5;
	
	//3.SPI����	SPI1->CR1
	SPI1->CR1 = 0x0327;
	SPI1->CR1 |= 1<<6;
	briupSpiWR( 0xff);
}

//SPI�����շ��ӿ�
u8	briupSpiWR(	u8 data)
{
	while( !( SPI1->SR & 0x02));
	SPI1->DR = data;
	while( !( SPI1->SR & 0x01));
	return SPI1->DR;
}

//SPI�ٶ����ýӿ�
void briupSpiSpeedSet( u8 speed)
{
	speed &= 0x07;
	while( SPI1->SR & (1<<7));
	SPI1->CR1 &= ~(0x07 << 3);
	SPI1->CR1 |= speed << 3;
	SPI1->CR1 |= 1<<6;
}

