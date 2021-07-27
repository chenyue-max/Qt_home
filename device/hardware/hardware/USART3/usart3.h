#ifndef __RFID_USART_H_
#define __RFID_USART_H_
#include <stm32f10x_map.h>



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:			usart_init(u32 pclk2,u32 bound)
 * Description: 	��Ƶ�����ڳ�ʼ��
 * Input: 				PCLK2��	ʱ��Ƶ��(Mhz)    	bound:������
 * Output: 				NULL
 * Return: 				NULL
 * Others: 				����ʱ��Ƶ�ʺͲ����ʣ���Ƶ�����ڳ�ʼ��
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
void usart3_init(u32 pclk2,u32 bound);
void Usart3_send(u16 len,u8* buf);


#endif
