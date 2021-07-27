#ifndef __DEBUG_USART_H_
#define __DEBUG_USART_H_
#include <stm32f10x_map.h>

#define USART_BUFFER_LEN 50
#define USART_TX_STANDBY 0
#define USART_TX_TRANSMITTING 1



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:				usart_init(u32 pclk2,u32 bound)
 * Description:		  ��ʼ��IO ����1�����Դ��ڣ�
 * Input: 					ʱ��Ƶ��(Mhz)    	bound:������
 * Output: 					NULL
 * Return: 					NULL
 * Others: 					����ʱ��Ƶ�ʺͲ����ʣ���ʼ��IO ����1��DMAͨ��4 USART TX ͨ��5 USART RX
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void usart_init(u32 pclk2,u32 bound);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		usart_read(u16 want_len,u8* buf)
 * Description: ����1�����Դ��ڣ���ȡ ͬʱά��ѭ������ָ��
 * Input:  			want_len�����USART_BUFFER_LEN���ֽ�  	u8* buf�����ջ������
 * Output:			NULL
 * Return: 			current_count�����ڵļ���
 * Others: 			����1��ȡ ͬʱά��ѭ������ָ�룬���ջ������,���USART_BUFFER_LEN���ֽ�.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
u8 usart_read(u16 len,u8* buf);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		 put_c(u16 len,u8* buf)
 * Description:  ����1�����Դ��ڣ�����ָ�����ȵ��ַ�
 * Input: 			 len ����   buf ��ַ
 * Output:			 NULL
 * Return:			 NULL
 * Others:			 NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void put_c(u16 len,u8* buf);

#endif
