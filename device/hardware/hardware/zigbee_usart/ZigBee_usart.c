#include "ZigBee_usart.h"
#include "jpstm32_sysclk.h"
volatile u8 ZigBee_usart_tx_status = ZigBee_USART_TX_STANDBY;
volatile u8 zigbee_buffer_overflow_flag = 0;
volatile u8 ZigbeeR_Size;
volatile u8 ZigbeeR_Finish=0;

//zigbee缓冲区 循环队列
//USARTX_Date zigbee_buffer;
u8 zigbee_buffer[ZIGBEE_BUFFER_LEN];
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		void USART2_IRQHandler(void)
 * Description: zigbee串口接收中断
 * Input: 			NULL
 * Output: 			NULL
 * Return:			NULL
 * Others: 			
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void USART2_IRQHandler(void)
{
	 u8 temp = 0;
   if( (USART2->SR & (1<<4)) == (1<<4) ) 
   {
      //USART1->SR &= ~(1<<4);
      temp = USART2->DR;//先读SR后读DR清中断  
   }
	 ZigbeeR_Size = ZIGBEE_BUFFER_LEN - DMA1_Channel6->CNDTR;//判断总共接收了多少个字节
	 ZigbeeR_Finish = 1;
	 DMA1_Channel6->CCR&=~(1<<0);//关闭DMA1通道6
	 DMA1_Channel6->CNDTR = ZIGBEE_BUFFER_LEN;//初始化计数器的值
	 DMA1_Channel6->CCR|=1<<0;//使能DMA传输
	 
}


//串口1发送完成DMA中断处理
void DMA1_Channel7_IRQHandler(void)
{
	u16 i;
    if( (DMA1->ISR & (1<<25)) == (1<<25) )
    //USART2 TX传输完成
    {
        DMA1->IFCR |= (1<<24);//清除标志位
				for(i=0;i<zigbee_buffer[2]+5;i++)
					zigbee_buffer[i]=0;
        DMA1_Channel7->CCR &= ~( (1<<0)|(1<<1) );//关闭DMA1通道4 关闭中断
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		zigbee_usart_init(u32 pclk2,u32 bound)
 * Description: zigbee串口初始化
 * Input: 			PCLK2：时钟频率(Mhz)    	bound:波特率
 * Output: 			NULL
 * Return:			NULL
 * Others: 			输入时钟频率和波特率，zigbee串口初始化
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void zigbee_usart_init(u32 pclk2,u32 bound)
{
  float temp;
	u16 mantissa,fraction;

	temp = (float)(pclk2 * 1000000)/(bound * 16);
	mantissa = temp;
	fraction = (temp - mantissa)*16;
	mantissa = (mantissa<<4) + fraction;

  RCC->APB2ENR |= 1<<2;
	GPIOA->CRL &= 0xffff000f;
	GPIOA->CRL |= 0x00008b20;
    
  ZIGBEE_RESET;//复位ZigBee
    
  RCC->APB1RSTR |= (1<<17);
  RCC->APB1RSTR &= ~(1<<17);
  RCC->APB1ENR |= (1<<17);
    
	USART2->BRR = mantissa;//设置波特率

#if 0//中断模式
    USART2->CR1 |= (1<<13)|(1<<5)|(1<<3)|(1<<2);//IDLE INTERRUPT
#else //DMA模式
    USART2->CR1 |= (1<<13)|(1<<4)|(1<<3)|(1<<2);//IDLE INTERRUPT
    USART2->CR3 |= (1<<6)|(1<<7);//DMAR DMAT
    
    RCC->AHBENR |= (1<<0);//DMA1 ENR
    delayMs(5);
    
    DMA1_Channel7->CCR &= ~(0XFFFFFFFF); 
    DMA1_Channel7->CNDTR = 0;
    DMA1_Channel7->CPAR = (u32)&(USART2->DR);
    DMA1_Channel7->CMAR = 0;
    DMA1_Channel7->CCR |= (1<<7)|(1<<4)|(1<<1);
    //中优先级 存储器地址增量 从存储器读 传输完成中断
    
    DMA1_Channel6->CCR &= ~(0XFFFFFFFF);
    DMA1_Channel6->CPAR = (u32)&(USART2->DR);
    DMA1_Channel6->CMAR = (u32)(zigbee_buffer);
    DMA1_Channel6->CNDTR = ZIGBEE_BUFFER_LEN;
    DMA1_Channel6->CCR |= (1<<13)|(1<<12)|(1<<7)|(1<<1)|(1<<0);
    //最高优先级 存储器地址增量 从外设读 允许传输完成中断 启动传输通道

    USART2->SR |= 0x1ff;
	MY_NVIC_Init(1,2,USART2_IRQChannel,2);
	MY_NVIC_Init(1,2,DMA1_Channel7_IRQChannel,2);
#endif
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		zigbee_send(u16 len,u8* buf)
 * Description: zigbee串口发送指定长度的字符
 * Input:  			len 长度   buf 地址
 * Output: 			NULL
 * Return: 			NULL
 * Others: 			NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void zigbee_send(u16 len,u8* buf)
{      
	 DMA1_Channel7->CCR &=~(1<<0);//关闭DMA传输
    DMA1_Channel7->CMAR = (u32)buf;
    DMA1_Channel7->CNDTR = len;
    DMA1_Channel7->CCR |= (1<<0);//|(1<<1);//启动DMA发送 开启中断
}
