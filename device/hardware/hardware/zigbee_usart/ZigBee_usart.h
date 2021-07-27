#ifndef __ZIGBEE_USART_H_
#define __ZIGBEE_USART_H_
#include <stm32f10x_map.h>
#include "sys.h"

#define ZIGBEE_BUFFER_LEN 256

#define ZigBee_USART_TX_TRANSMITTING 1
#define ZigBee_USART_TX_STANDBY 0
#define BUFFER_LEN             256


extern volatile u8 ZigbeeR_Size;
extern volatile u8 ZigbeeR_Finish;
extern u8 zigbee_buffer[ZIGBEE_BUFFER_LEN];


#define ZIGBEE_RESET 		do{PAout(1) = 0;delayMs(100);PAout(1) = 1;}while(0);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		zigbee_usart_init(u32 pclk2,u32 bound)
 * Description: zigbee���ڳ�ʼ��
 * Input: 			PCLK2��ʱ��Ƶ��(Mhz)    	bound:������
 * Output: 			NULL
 * Return:			NULL
 * Others: 			����ʱ��Ƶ�ʺͲ����ʣ�zigbee���ڳ�ʼ��
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void zigbee_usart_init(u32 pclk2,u32 bound);
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		zigbee_read(u16 want_len,u8* buf)
 * Description: zigbee���ڶ�ȡ 
 * Input: 			want_len�����USART_BUFFER_LEN���ֽ�  	u8* buf�����ջ������
 * Output:		 	NULL
 * Return: 			current_count�����ڵļ���
 * Others: 			zigbee���ڶ�ȡ ���ջ������,���USART_BUFFER_LEN���ֽ�.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
u8 zigbee_read(u16 want_len,u8* buf);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		zigbee_send(u16 len,u8* buf)
 * Description: zigbee���ڷ���ָ�����ȵ��ַ�
 * Input:  			len ����   buf ��ַ
 * Output: 			NULL
 * Return: 			NULL
 * Others: 			NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void zigbee_send(u16 len,u8* buf);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		 get_direction(void)
 * Description:  ��ѭ�������ж�ȡ����
 * Input:  			 NULL
 * Output:			 NULL
 * Return:			 NULL
 * Others: 			 ��ѭ�������ж�ȡ����
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void get_direction(void);

#endif
