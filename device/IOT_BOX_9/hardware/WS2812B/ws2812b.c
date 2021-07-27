#include "ws2812b.h"
#include "jpstm32_gpio.h"
#include "jpstm32_sysclk.h"
#include "sys.h"

u16 PixelBuffer[1637];//16*32,第0位永远为0用于传输完成拉低总线。

void ws2812b_init(void)
{
	u16 i=0;
	//使能SPI1的时钟
	RCC->APB2ENR |= 1<<12;
	//使能DMA1的时钟
	RCC->AHBENR |= 1<<0;
	//使能A的时钟
	RCC->APB2ENR |= 1<<2;

	//初始化GPIOA7
	GPIOA->CRL &= 0x0FFFFFFF;
	//配置GPOA7为复用输出
	GPIOA->CRL |= 0xB0000000;

	//SPI1的配置
	SPI1->CR1 |= 1<<15;//单线双向模式
	SPI1->CR1 |= 1<<14;//单线只发模式
	SPI1->CR1 |= 1<<11;//16位数据格式
	SPI1->CR1 |= 1<<9;//软件管理从机选择（nss管理）
	SPI1->CR1 |= 1<<8;//内部设备选择
	SPI1->CR1 |= 0<<7; //MSB信号发出
	SPI1->CR1 |= 1<<3;//4分频
	SPI1->CR1 |= 1<<2;//SPI主设备
	SPI1->CR1 &= ~0x02;//空闲状态下SCK为0 ，CPOL=0
	SPI1->CR1 &= ~0x01;//数据采样从第一个时间边沿开始APHA=0

	SPI1->CR2 |= 1<<1;//启动DMA发送缓存
	SPI1->CR1 |= 1<<6;//使能SPI设备

	DMA1_Channel3->CCR |= 1<<12;//中优先级
	DMA1_Channel3->CCR |= 1<<10;//存储器数据宽度16位
	DMA1_Channel3->CCR |= 1<<8;//外设数据宽度16位
	DMA1_Channel3->CCR |= 1<<7;//存储器增量地址增量模式
	DMA1_Channel3->CCR |= 1<<4;//从存储器度
	DMA1_Channel3->CNDTR = 0;//传输数据量为0
	DMA1_Channel3->CPAR = (u32)&(SPI1->DR);//外设地址
	DMA1_Channel3->CMAR = (u32)PixelBuffer;//存储器地址

	for(i=0;i<1536;i++)
	{
		PixelBuffer[i+100] = 0x0000;
	}
	
}

//使能函数
void ws2812b_en(void)
{
	DMA1_Channel3->CCR &= ~(1<<0);//关闭通道3
	DMA1_Channel3->CNDTR = 1637;//初始化计数器的值
	DMA1_Channel3->CCR |= 1<<0;//开启
}

void ws2812b_pixel_en(u8 x, u8 y, u8 len, u32* RGB_Value, u8 mode)
{
	u16 Pixel_Point = 0;
	u16 One = 0xFFC0;
	u16 Zero = 0xF000;
	u32 i;
	Pixel_Point = (Y_LEN*y + x)*24+100;
	while(len--)
	{
		for(i=0x800000;i>=0x01;i>>=1)
		{
			PixelBuffer[Pixel_Point] = (*RGB_Value)&i?One:Zero;
			Pixel_Point++;
		}
		if(mode == 1)
			RGB_Value ++;
	}
	ws2812b_en();//重置DMA计数
}
//熄灭所有的灯
void ws2812b_clear(void)
{
	u16 i;
	for(i=0;i<1536;i++)
	{
		PixelBuffer[i+100] = 0xF000;
	}
	ws2812b_en();
}


