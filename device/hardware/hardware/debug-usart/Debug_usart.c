#include "Debug_usart.h"
#include "jpstm32_sysclk.h"
#include "sys.h"
volatile u8 usart_tx_status = USART_TX_STANDBY;
volatile u8 usart_buffer_overflow_flag = 0;
volatile u8 Usart1_RFinish = 0;
u8 Usart1_RBuffer[USART_BUFFER_LEN];
//串口1缓冲区 循环队列
struct
{
    u8 data[USART_BUFFER_LEN];
    volatile u16 front;
    volatile u16 tail;
    volatile u16 size;
}usart_buffer;

void USART1_IRQHandler(void)
{
	 u8 temp = 0;
   if( (USART1->SR & (1<<4)) == (1<<4) ) 
   {
      //USART1->SR &= ~(1<<4);
      temp = USART1->DR;//先读SR后读DR清中断  
   }
	 usart_buffer.size = USART_BUFFER_LEN - DMA1_Channel5->CNDTR;//判断总共接收了多少个字节
	 Usart1_RFinish = 1;
	 DMA1_Channel5->CCR&=~(1<<0);//关闭DMA1通道6
	 DMA1_Channel5->CNDTR = USART_BUFFER_LEN;//初始化计数器的值
	 DMA1_Channel5->CCR|=1<<0;//使能DMA传输
	 
}



    

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:				usart_init(u32 pclk2,u32 bound)
 * Description:		  初始化IO 串口1（调试串口）
 * Input: 					时钟频率(Mhz)    	bound:波特率
 * Output: 					NULL
 * Return: 					NULL
 * Others: 					输入时钟频率和波特率，初始化IO 串口1，DMA通道4 USART TX 通道5 USART RX
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void usart_init(u32 pclk2,u32 bound)
{
	float temp;
	u16 mantissa,fraction;
	temp = (float)(pclk2 * 1000000)/(bound * 16);
	mantissa = temp;
	fraction = (temp - mantissa)*16;
	mantissa = (mantissa<<4) + fraction;
	
	
	RCC->AHBENR |= (1<<0);//使能DMA1的时钟
  RCC->APB2ENR |= 1<<2;//使能POARTA的时钟
	GPIOA->CRH &= 0xfffff00f;
	GPIOA->CRH |= 0x000008B0;//配置相应的管脚模式
	RCC->APB2RSTR |= 1<<14;	//复位设备
	RCC->APB2RSTR &= ~(1<<14);//停止复位
	RCC->APB2ENR |= 1<<14;//使能串口时钟
	USART1->BRR = mantissa;//将计算好的波特率赋值到相应的寄存器中

  //USART1->CR3 |= (1<<6)|(1<<7);//DMAR DMAT

  USART1->SR |= 0x1ff;

	delayMs(5);
	
  USART1->CR1 |= (1<<13)|(1<<4)|(1<<3)|(1<<2);//IDLE INTERRUPT
  USART1->CR3 |= (1<<6)|(1<<7);//DMAR DMAT

 
	DMA1_Channel4->CCR &= ~(0XFFFFFFFF); 
	DMA1_Channel4->CNDTR = 0;
	DMA1_Channel4->CPAR = (u32)&(USART1->DR);
	DMA1_Channel4->CMAR = 0;
	DMA1_Channel4->CCR |= (1<<7)|(1<<4)|(1<<1);
	//中优先级 存储器地址增量 从存储器读 传输完成中断

	DMA1_Channel5->CCR &= ~(0XFFFFFFFF);
	DMA1_Channel5->CPAR = (u32)&(USART1->DR);
	DMA1_Channel5->CMAR = (u32)(Usart1_RBuffer);
	DMA1_Channel5->CNDTR = USART_BUFFER_LEN;
	DMA1_Channel5->CCR |= (1<<13)|(1<<12)|(1<<7)|(1<<1)|(1<<0);
	//存储器地址增量 从外设读 循环模式 允许传输完成中断 启动传输通道

	MY_NVIC_Init(2,0,USART1_IRQChannel,2);
	MY_NVIC_Init(1,3,DMA1_Channel5_IRQChannel,2);
	usart_buffer.front = 0;
	usart_buffer.size = 0;
	usart_buffer.tail = 0;

#if 0 
  usart_tim_init(2);//0.1ms * period
#endif
}




/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		usart_read(u16 want_len,u8* buf)
 * Description: 串口1（调试串口）读取 同时维护循环队列指针
 * Input:  			want_len：最大USART_BUFFER_LEN个字节  	u8* buf：接收缓冲队列
 * Output:			NULL
 * Return: 			current_count：现在的计数
 * Others: 			串口1读取 同时维护循环队列指针，接收缓冲队列,最大USART_BUFFER_LEN个字节.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
u8 usart_read(u16 want_len,u8* buf)
{
    //DMA 循环队列
    u16 i,current_count = 0;
    usart_buffer.tail = (USART_BUFFER_LEN - DMA1_Channel5->CNDTR);//最后一个有数据的位置
    if(usart_buffer.tail > usart_buffer.front)
    {
        current_count = usart_buffer.tail - usart_buffer.front;
        usart_buffer_overflow_flag = 0;//尾巴在后 没有发生溢出
    }
    else if(usart_buffer.tail < usart_buffer.front)
    {
        current_count = usart_buffer.tail + USART_BUFFER_LEN - (usart_buffer.front);
    }
    else
    {
        current_count = 0;
    }
    
    if( (want_len != 0) && (want_len < current_count) )
    {
        current_count = want_len;
    }
    for(i = 0; i < current_count; i++)
    {
        buf[i] = usart_buffer.data[usart_buffer.front];
        usart_buffer.front = (usart_buffer.front + 1) % USART_BUFFER_LEN;
    }
    return current_count;
}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		 put_c(u16 len,u8* buf)
 * Description:  串口1（调试串口）发送指定长度的字符
 * Input: 			 len 长度   buf 地址
 * Output:			 NULL
 * Return:			 NULL
 * Others:			 NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void put_c(u16 len,u8* buf)
{   DMA1_Channel4->CCR &=~(1<<0);//关闭DMA传输   
    DMA1_Channel4->CMAR = (u32)buf;
    DMA1_Channel4->CNDTR = len;
    DMA1_Channel4->CCR |= (1<<0);//|(1<<1);//启动DMA发送 开启中断
}






