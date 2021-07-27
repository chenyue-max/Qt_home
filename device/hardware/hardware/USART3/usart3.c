#define BUFFER_LEN	50 

#include "usart3.h"
#include "jpstm32_sysclk.h"
#include "sys.h"

u8 UsartDataLen = 0;
u8 Usart3Buffer[BUFFER_LEN] = {0};
u8 Usart3RX_L = 0;//串口三接收数据的长度
volatile u8 UsartR_Finished = 0;
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:			usart3_init(u32 pclk2,u32 bound)
 * Description: 	串口3初始化
 * Input: 				PCLK2：	时钟频率(Mhz)    	bound:波特率
 * Output: 				NULL
 * Return: 				NULL
 * Others: 				输入时钟频率和波特率，射频卡串口初始化
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void usart3_init(u32 pclk2,u32 bound)
{
   float temp;
	u16 mantissa,fraction;
         
	temp = (float)(pclk2 * 1000000)/(bound * 16);
	mantissa = temp;
	fraction = (temp - mantissa)*16;
	mantissa = (mantissa<<4) + fraction;

  RCC->APB2ENR |= 1<<3;
	GPIOB->CRH &= 0xffff00ff;
	GPIOB->CRH |= 0x00008b00;
    
  RCC->APB1RSTR |= (1<<18);
  RCC->APB1RSTR &= ~(1<<18);
  RCC->APB1ENR |= (1<<18);
    
	USART3->BRR = mantissa;

#if 0//中断模式
    USART3->CR1 |= (1<<13)|(1<<4)|(1<<5)|(1<<2);//IDLE INTERRUPT
#else //DMA模式
	 USART3->CR1 |= (1<<13)|(1<<4)|(1<<3)|(1<<2);//IDLE INTERRUPT
    USART3->CR3 |= (1<<6)|(1<<7);//DMAR DMAT
    
    RCC->AHBENR |= (1<<0);//DMA1 ENR
    delayMs(5);
    
    DMA1_Channel2->CCR &= ~(0XFFFFFFFF); 
    DMA1_Channel2->CNDTR = 0;
    DMA1_Channel2->CPAR = (u32)&(USART3->DR);
    DMA1_Channel2->CMAR = 0;
    DMA1_Channel2->CCR |= (1<<7)|(1<<4)|(1<<1);
    //中优先级 存储器地址增量 从存储器读 传输完成中断
    
    DMA1_Channel3->CCR &= ~(0XFFFFFFFF);//初始化CCR寄存器
    DMA1_Channel3->CPAR = (u32)&(USART3->DR);//串口3外设地址
    DMA1_Channel3->CMAR = (u32)(Usart3Buffer);
    DMA1_Channel3->CNDTR = BUFFER_LEN;
    DMA1_Channel3->CCR |= (1<<13)|(0<<12)|(1<<7)|(1<<1)|(1<<0);
    //高优先级 存储器地址增量 从外设读 循环模式 允许传输完成中断 启动传输通道
		MY_NVIC_Init(1,1,USART3_IRQChannel,2);
		MY_NVIC_Init(1,1,DMA1_Channel3_IRQChannel,2);
#endif
    USART3->SR = 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		void USART3_IRQHandler(void)
 * Description: usart3接收中断
 * Input: 			NULL
 * Output: 			NULL
 * Return:			NULL
 * Others: 			
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void USART3_IRQHandler(void)
{
	u8 temp;
   if( (USART3->SR & (1<<4)) == (1<<4) ) 
   {
      //USART1->SR &= ~(1<<4);
      temp = USART3->DR;//先读SR后读DR清中断  
   }
	 Usart3RX_L = BUFFER_LEN - DMA1_Channel3->CNDTR;//判断总共接收了多少个字节
	 UsartR_Finished = 1;
	 DMA1_Channel3->CCR&=~(1<<0);//关闭DMA1通道6
	 DMA1_Channel3->CNDTR = BUFFER_LEN;//初始化计数器的值
	 DMA1_Channel3->CCR|=1<<0;//使能DMA传输
	 
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		zigbee_send(u16 len,u8* buf)
 * Description: zigbee串口发送指定长度的字符
 * Input:  			len 长度   buf 地址
 * Output: 			NULL
 * Return: 			NULL
 * Others: 			NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Usart3_send(u16 len,u8* buf)
{      
	  DMA1_Channel2->CCR &=~(1<<0);//关闭DMA传输

		DMA1_Channel2->CMAR = (u32)buf;
    DMA1_Channel2->CNDTR = len;
    DMA1_Channel2->CCR |= (1<<0);//|(1<<1);//启动DMA发送 开启中断
}
