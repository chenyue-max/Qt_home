#include "Debug_usart.h"
#include "jpstm32_sysclk.h"
#include "sys.h"
volatile u8 usart_tx_status = USART_TX_STANDBY;
volatile u8 usart_buffer_overflow_flag = 0;
volatile u8 Usart1_RFinish = 0;
u8 Usart1_RBuffer[USART_BUFFER_LEN];
//����1������ ѭ������
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
      temp = USART1->DR;//�ȶ�SR���DR���ж�  
   }
	 usart_buffer.size = USART_BUFFER_LEN - DMA1_Channel5->CNDTR;//�ж��ܹ������˶��ٸ��ֽ�
	 Usart1_RFinish = 1;
	 DMA1_Channel5->CCR&=~(1<<0);//�ر�DMA1ͨ��6
	 DMA1_Channel5->CNDTR = USART_BUFFER_LEN;//��ʼ����������ֵ
	 DMA1_Channel5->CCR|=1<<0;//ʹ��DMA����
	 
}



    

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:				usart_init(u32 pclk2,u32 bound)
 * Description:		  ��ʼ��IO ����1�����Դ��ڣ�
 * Input: 					ʱ��Ƶ��(Mhz)    	bound:������
 * Output: 					NULL
 * Return: 					NULL
 * Others: 					����ʱ��Ƶ�ʺͲ����ʣ���ʼ��IO ����1��DMAͨ��4 USART TX ͨ��5 USART RX
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void usart_init(u32 pclk2,u32 bound)
{
	float temp;
	u16 mantissa,fraction;
	temp = (float)(pclk2 * 1000000)/(bound * 16);
	mantissa = temp;
	fraction = (temp - mantissa)*16;
	mantissa = (mantissa<<4) + fraction;
	
	
	RCC->AHBENR |= (1<<0);//ʹ��DMA1��ʱ��
  RCC->APB2ENR |= 1<<2;//ʹ��POARTA��ʱ��
	GPIOA->CRH &= 0xfffff00f;
	GPIOA->CRH |= 0x000008B0;//������Ӧ�Ĺܽ�ģʽ
	RCC->APB2RSTR |= 1<<14;	//��λ�豸
	RCC->APB2RSTR &= ~(1<<14);//ֹͣ��λ
	RCC->APB2ENR |= 1<<14;//ʹ�ܴ���ʱ��
	USART1->BRR = mantissa;//������õĲ����ʸ�ֵ����Ӧ�ļĴ�����

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
	//�����ȼ� �洢����ַ���� �Ӵ洢���� ��������ж�

	DMA1_Channel5->CCR &= ~(0XFFFFFFFF);
	DMA1_Channel5->CPAR = (u32)&(USART1->DR);
	DMA1_Channel5->CMAR = (u32)(Usart1_RBuffer);
	DMA1_Channel5->CNDTR = USART_BUFFER_LEN;
	DMA1_Channel5->CCR |= (1<<13)|(1<<12)|(1<<7)|(1<<1)|(1<<0);
	//�洢����ַ���� ������� ѭ��ģʽ ����������ж� ��������ͨ��

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
 * Description: ����1�����Դ��ڣ���ȡ ͬʱά��ѭ������ָ��
 * Input:  			want_len�����USART_BUFFER_LEN���ֽ�  	u8* buf�����ջ������
 * Output:			NULL
 * Return: 			current_count�����ڵļ���
 * Others: 			����1��ȡ ͬʱά��ѭ������ָ�룬���ջ������,���USART_BUFFER_LEN���ֽ�.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
u8 usart_read(u16 want_len,u8* buf)
{
    //DMA ѭ������
    u16 i,current_count = 0;
    usart_buffer.tail = (USART_BUFFER_LEN - DMA1_Channel5->CNDTR);//���һ�������ݵ�λ��
    if(usart_buffer.tail > usart_buffer.front)
    {
        current_count = usart_buffer.tail - usart_buffer.front;
        usart_buffer_overflow_flag = 0;//β���ں� û�з������
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
 * Description:  ����1�����Դ��ڣ�����ָ�����ȵ��ַ�
 * Input: 			 len ����   buf ��ַ
 * Output:			 NULL
 * Return:			 NULL
 * Others:			 NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void put_c(u16 len,u8* buf)
{   DMA1_Channel4->CCR &=~(1<<0);//�ر�DMA����   
    DMA1_Channel4->CMAR = (u32)buf;
    DMA1_Channel4->CNDTR = len;
    DMA1_Channel4->CCR |= (1<<0);//|(1<<1);//����DMA���� �����ж�
}






