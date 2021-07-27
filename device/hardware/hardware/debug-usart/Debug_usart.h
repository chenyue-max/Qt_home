#ifndef __DEBUG_USART_H_
#define __DEBUG_USART_H_
#include <stm32f10x_map.h>

#define USART_BUFFER_LEN 50
#define USART_TX_STANDBY 0
#define USART_TX_TRANSMITTING 1



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:				usart_init(u32 pclk2,u32 bound)
 * Description:		  初始化IO 串口1（调试串口）
 * Input: 					时钟频率(Mhz)    	bound:波特率
 * Output: 					NULL
 * Return: 					NULL
 * Others: 					输入时钟频率和波特率，初始化IO 串口1，DMA通道4 USART TX 通道5 USART RX
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void usart_init(u32 pclk2,u32 bound);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		usart_read(u16 want_len,u8* buf)
 * Description: 串口1（调试串口）读取 同时维护循环队列指针
 * Input:  			want_len：最大USART_BUFFER_LEN个字节  	u8* buf：接收缓冲队列
 * Output:			NULL
 * Return: 			current_count：现在的计数
 * Others: 			串口1读取 同时维护循环队列指针，接收缓冲队列,最大USART_BUFFER_LEN个字节.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
u8 usart_read(u16 len,u8* buf);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:		 put_c(u16 len,u8* buf)
 * Description:  串口1（调试串口）发送指定长度的字符
 * Input: 			 len 长度   buf 地址
 * Output:			 NULL
 * Return:			 NULL
 * Others:			 NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void put_c(u16 len,u8* buf);

#endif
