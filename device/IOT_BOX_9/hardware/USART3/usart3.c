#define BUFFER_LEN	50 

#include "usart3.h"
#include "jpstm32_sysclk.h"
#include "sys.h"

u8 UsartDataLen = 0;
u8 Usart3Buffer[BUFFER_LEN] = {0};
u8 Usart3RX_L = 0;//�������������ݵĳ���
volatile u8 UsartR_Finished = 0;
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:			usart3_init(u32 pclk2,u32 bound)
 * Description: 	����3��ʼ��
 * Input: 				PCLK2��	ʱ��Ƶ��(Mhz)    	bound:������
 * Output: 				NULL
 * Return: 				NULL
 * Others: 				����ʱ��Ƶ�ʺͲ����ʣ���Ƶ�����ڳ�ʼ��
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

#if 0//�ж�ģʽ
    USART3->CR1 |= (1<<13)|(1<<4)|(1<<5)|(1<<2);//IDLE INTERRUPT
#else //DMAģʽ
	 USART3->CR1 |= (1<<13)|(1<<4)|(1<<3)|(1<<2);//IDLE INTERRUPT
    USART3->CR3 |= (1<<6)|(1<<7);//DMAR DMAT
    
    RCC->AHBENR |= (1<<0);//DMA1 ENR
    delayMs(5);
    
    DMA1_Channel2->CCR &= ~(0XFFFFFFFF); 
    DMA1_Channel2->CNDTR = 0;
    DMA1_Channel2->CPAR = (u32)&(USART3->DR);
    DMA1_Channel2->CMAR = 0;
    DMA1_Channel2->CCR |= (1<<7)|(1<<4)|(1<<1);
    //�����ȼ� �洢����ַ���� �Ӵ洢���� ��������ж�
    
    DMA1_Channel3->CCR &= ~(0XFFFFFFFF);//��ʼ��CCR�Ĵ���
    DMA1_Channel3->CPAR = (u32)&(USART3->DR);//����3�����ַ
    DMA1_Channel3->CMAR = (u32)(Usart3Buffer);
    DMA1_Channel3->CNDTR = BUFFER_LEN;
    DMA1_Channel3->CCR |= (1<<13)|(0<<12)|(1<<7)|(1<<1)|(1<<0);
    //�����ȼ� �洢����ַ���� ������� ѭ��ģʽ ����������ж� ��������ͨ��
		MY_NVIC_Init(1,1,USART3_IRQChannel,2);
		MY_NVIC_Init(1,1,DMA1_Channel3_IRQChannel,2);
#endif
    USART3->SR = 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		void USART3_IRQHandler(void)
 * Description: usart3�����ж�
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
      temp = USART3->DR;//�ȶ�SR���DR���ж�  
   }
	 Usart3RX_L = BUFFER_LEN - DMA1_Channel3->CNDTR;//�ж��ܹ������˶��ٸ��ֽ�
	 UsartR_Finished = 1;
	 DMA1_Channel3->CCR&=~(1<<0);//�ر�DMA1ͨ��6
	 DMA1_Channel3->CNDTR = BUFFER_LEN;//��ʼ����������ֵ
	 DMA1_Channel3->CCR|=1<<0;//ʹ��DMA����
	 
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		zigbee_send(u16 len,u8* buf)
 * Description: zigbee���ڷ���ָ�����ȵ��ַ�
 * Input:  			len ����   buf ��ַ
 * Output: 			NULL
 * Return: 			NULL
 * Others: 			NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Usart3_send(u16 len,u8* buf)
{      
	  DMA1_Channel2->CCR &=~(1<<0);//�ر�DMA����

		DMA1_Channel2->CMAR = (u32)buf;
    DMA1_Channel2->CNDTR = len;
    DMA1_Channel2->CCR |= (1<<0);//|(1<<1);//����DMA���� �����ж�
}
