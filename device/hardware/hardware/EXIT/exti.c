#include "exti.h"
#include "sys.h"
#include "iic_master.h"
#include "jpstm32_gpio.h"
#include "jpstm32_sysclk.h"
#include "Debug_usart.h"

volatile u8 key_value =0;
volatile u8 door_page =0x00;
volatile u8 Open_type = 0xFF;

//�ⲿ�ж�4�������/
void EXTI15_10_IRQHandler(void)
{ 
	EXTI->PR=1<<13;  //���LINE�ϵ��жϱ�־λ  
	IIC_M_Start();
	IIC_M_Send_Byte(0XBA);
	if(IIC_M_Wait_Ack()){IIC_M_Stop(); return ;}
   key_value = IIC_M_Read_Byte(0);
//   if(key_value == 0x11)
//      door_page = door_page?0:1;
   switch(key_value)
   {
      case 0x0C:
         Open_type = 0x01;
         break;
      case 0x0D:
          Open_type = 0x02;
          break;
      case 0x0E:
         Open_type = 0x03;
         break;
      case 0x11:
         
         Open_type = 0x11;
      default:
         break;
   }
	IIC_M_Stop();
	//put_c(1,&value);
	EXTI->PR=1<<13;  //���LINE�ϵ��жϱ�־λ 
}		   

//�ⲿ�жϳ�ʼ������
//��ʼ��PC13Ϊ�ⲿ�жϣ������س����ж�
//
//

void EXTIX_Init(void)
{
  RCC->APB2ENR|=1<<4;
	GPIOA->CRH&=0xff0ffffF;
	GPIOA->CRH|=0x00800000;
	Ex_NVIC_Config(GPIO_C,13,RTIR); 			//�����ش���
	MY_NVIC_Init(1,0,EXTI15_10_IRQChannel,3);	//��ռ2�������ȼ�0����2	   
}

