#include "ZigBee_usart.h"
#include "jpstm32_sysclk.h"
volatile u8 ZigBee_usart_tx_status = ZigBee_USART_TX_STANDBY;
volatile u8 zigbee_buffer_overflow_flag = 0;
volatile u8 ZigbeeR_Size;
volatile u8 ZigbeeR_Finish=0;

//zigbee������ ѭ������
//USARTX_Date zigbee_buffer;
u8 zigbee_buffer[ZIGBEE_BUFFER_LEN];
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		void USART2_IRQHandler(void)
 * Description: zigbee���ڽ����ж�
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
      temp = USART2->DR;//�ȶ�SR���DR���ж�  
   }
	 ZigbeeR_Size = ZIGBEE_BUFFER_LEN - DMA1_Channel6->CNDTR;//�ж��ܹ������˶��ٸ��ֽ�
	 ZigbeeR_Finish = 1;
	 DMA1_Channel6->CCR&=~(1<<0);//�ر�DMA1ͨ��6
	 DMA1_Channel6->CNDTR = ZIGBEE_BUFFER_LEN;//��ʼ����������ֵ
	 DMA1_Channel6->CCR|=1<<0;//ʹ��DMA����
	 
}


//����1�������DMA�жϴ���
void DMA1_Channel7_IRQHandler(void)
{
	u16 i;
    if( (DMA1->ISR & (1<<25)) == (1<<25) )
    //USART2 TX�������
    {
        DMA1->IFCR |= (1<<24);//�����־λ
				for(i=0;i<zigbee_buffer[2]+5;i++)
					zigbee_buffer[i]=0;
        DMA1_Channel7->CCR &= ~( (1<<0)|(1<<1) );//�ر�DMA1ͨ��4 �ر��ж�
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		zigbee_usart_init(u32 pclk2,u32 bound)
 * Description: zigbee���ڳ�ʼ��
 * Input: 			PCLK2��ʱ��Ƶ��(Mhz)    	bound:������
 * Output: 			NULL
 * Return:			NULL
 * Others: 			����ʱ��Ƶ�ʺͲ����ʣ�zigbee���ڳ�ʼ��
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
    
  ZIGBEE_RESET;//��λZigBee
    
  RCC->APB1RSTR |= (1<<17);
  RCC->APB1RSTR &= ~(1<<17);
  RCC->APB1ENR |= (1<<17);
    
	USART2->BRR = mantissa;//���ò�����

#if 0//�ж�ģʽ
    USART2->CR1 |= (1<<13)|(1<<5)|(1<<3)|(1<<2);//IDLE INTERRUPT
#else //DMAģʽ
    USART2->CR1 |= (1<<13)|(1<<4)|(1<<3)|(1<<2);//IDLE INTERRUPT
    USART2->CR3 |= (1<<6)|(1<<7);//DMAR DMAT
    
    RCC->AHBENR |= (1<<0);//DMA1 ENR
    delayMs(5);
    
    DMA1_Channel7->CCR &= ~(0XFFFFFFFF); 
    DMA1_Channel7->CNDTR = 0;
    DMA1_Channel7->CPAR = (u32)&(USART2->DR);
    DMA1_Channel7->CMAR = 0;
    DMA1_Channel7->CCR |= (1<<7)|(1<<4)|(1<<1);
    //�����ȼ� �洢����ַ���� �Ӵ洢���� ��������ж�
    
    DMA1_Channel6->CCR &= ~(0XFFFFFFFF);
    DMA1_Channel6->CPAR = (u32)&(USART2->DR);
    DMA1_Channel6->CMAR = (u32)(zigbee_buffer);
    DMA1_Channel6->CNDTR = ZIGBEE_BUFFER_LEN;
    DMA1_Channel6->CCR |= (1<<13)|(1<<12)|(1<<7)|(1<<1)|(1<<0);
    //������ȼ� �洢����ַ���� ������� ����������ж� ��������ͨ��

    USART2->SR |= 0x1ff;
	MY_NVIC_Init(1,2,USART2_IRQChannel,2);
	MY_NVIC_Init(1,2,DMA1_Channel7_IRQChannel,2);
#endif
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		zigbee_send(u16 len,u8* buf)
 * Description: zigbee���ڷ���ָ�����ȵ��ַ�
 * Input:  			len ����   buf ��ַ
 * Output: 			NULL
 * Return: 			NULL
 * Others: 			NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void zigbee_send(u16 len,u8* buf)
{      
	 DMA1_Channel7->CCR &=~(1<<0);//�ر�DMA����
    DMA1_Channel7->CMAR = (u32)buf;
    DMA1_Channel7->CNDTR = len;
    DMA1_Channel7->CCR |= (1<<0);//|(1<<1);//����DMA���� �����ж�
}
