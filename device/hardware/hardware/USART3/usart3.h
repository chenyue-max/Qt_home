#ifndef __RFID_USART_H_
#define __RFID_USART_H_
#include <stm32f10x_map.h>



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:			usart_init(u32 pclk2,u32 bound)
 * Description: 	射频卡串口初始化
 * Input: 				PCLK2：	时钟频率(Mhz)    	bound:波特率
 * Output: 				NULL
 * Return: 				NULL
 * Others: 				输入时钟频率和波特率，射频卡串口初始化
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
void usart3_init(u32 pclk2,u32 bound);
void Usart3_send(u16 len,u8* buf);


#endif
