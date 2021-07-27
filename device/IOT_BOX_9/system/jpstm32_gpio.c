/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * File name: jpstm32_gpio.c
 * Author: Duke An
 * Version: 0.1
 * Date: 2014-06-17
 * Description: ϵͳͨ��I/O�ӿ�ʵ��
 * Copyright @ 2013 by Briup Technology,Inc. All rights Reserved.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "jpstm32_gpio.h"
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	config_gpio
 * Description: ����GPIO�˿�
 * Input: 
 *	>PORTx,	�˿����� x=(A B C ...)
 *	>MODE, ���ģʽ����, �����趨�˿����Ƶ�� 
 *	>PINx, ��Ҫ���õ����� Pin0~PinF ���Խ��л����
 *	>PULL_STAT, ���������Ƿ�����
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void gpioConfig(u32 PORTx, u32 MODE, u32 PINxs, PULL_STAT stat)
{
	u8	i, j;
	//��ȡ��ǰ�˿ڵ�ַ
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
			//�ж��Ƿ���Ҫ����������
			if(!(MODE^(I_PULLUD|OMODE_RES)))
			{
				port->ODR &= ~(1<<i);
				port->ODR |= (stat<<i);
			}
		}
	}
}


