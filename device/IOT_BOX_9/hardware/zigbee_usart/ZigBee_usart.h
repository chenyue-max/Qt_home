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
 * Description: zigbee串口初始化
 * Input: 			PCLK2：时钟频率(Mhz)    	bound:波特率
 * Output: 			NULL
 * Return:			NULL
 * Others: 			输入时钟频率和波特率，zigbee串口初始化
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void zigbee_usart_init(u32 pclk2,u32 bound);
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		zigbee_read(u16 want_len,u8* buf)
 * Description: zigbee串口读取 
 * Input: 			want_len：最大USART_BUFFER_LEN个字节  	u8* buf：接收缓冲队列
 * Output:		 	NULL
 * Return: 			current_count：现在的计数
 * Others: 			zigbee串口读取 接收缓冲队列,最大USART_BUFFER_LEN个字节.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
u8 zigbee_read(u16 want_len,u8* buf);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		zigbee_send(u16 len,u8* buf)
 * Description: zigbee串口发送指定长度的字符
 * Input:  			len 长度   buf 地址
 * Output: 			NULL
 * Return: 			NULL
 * Others: 			NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void zigbee_send(u16 len,u8* buf);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		 get_direction(void)
 * Description:  从循环队列中读取命令
 * Input:  			 NULL
 * Output:			 NULL
 * Return:			 NULL
 * Others: 			 从循环队列中读取命令
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void get_direction(void);

#endif
