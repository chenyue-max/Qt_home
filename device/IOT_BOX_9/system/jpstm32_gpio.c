/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * File name: jpstm32_gpio.c
 * Author: Duke An
 * Version: 0.1
 * Date: 2014-06-17
 * Description: 系统通用I/O接口实现
 * Copyright @ 2013 by Briup Technology,Inc. All rights Reserved.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "jpstm32_gpio.h"
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	config_gpio
 * Description: 配置GPIO端口
 * Input: 
 *	>PORTx,	端口名称 x=(A B C ...)
 *	>MODE, 输出模式设置, 用于设定端口输出频率 
 *	>PINx, 需要设置的引脚 Pin0~PinF 可以进行或操作
 *	>PULL_STAT, 设置引脚是否上拉
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void gpioConfig(u32 PORTx, u32 MODE, u32 PINxs, PULL_STAT stat)
{
	u8	i, j;
	//获取当前端口地址
	GPIO_TypeDef*	port = (GPIO_TypeDef*)(GPIO_BASE+PORTx);
	for(i=0; i<16; i++){
		if(PINxs&(1<<i)){
			if(i<=7){
				port->CRL &= (0xFFFFFFFF&(~(0xF<<(i*4))));
				port->CRL |= MODE<<(i*4);
			} else {
				j = i%8;
				port->CRH &= (0xFFFFFFFF&(~(0xF<<(j*4))));
				port->CRH |= MODE<<(j*4);
			}
			//判断是否需要上拉或下拉
			if(!(MODE^(I_PULLUD|OMODE_RES)))
			{
				port->ODR &= ~(1<<i);
				port->ODR |= (stat<<i);
			}
		}
	}
}


