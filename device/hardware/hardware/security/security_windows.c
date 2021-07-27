/*******************************************************
文件功能：智能门窗相关传感器驱动配置
管脚连接：
				报警器		-->PB8
				报警灯		-->PB9
				光电开关	-->PB0
				对射开关	-->PB1
*******************************************************/
#include "security_windows.h"

void Security_Windows_GPIO_Init()
{
	RCC->APB2ENR |= 1<<3;//使能GPIOB时钟
	GPIOB->CRL &= 0XFFFFFF00;
	GPIOB->CRL |= 0X00000088;
	GPIOB->ODR |= (1<<1)|(1<<0);//使能上拉输入
	GPIOB->CRH &= 0XFFFFFF00;
	GPIOB->CRH |= 0X00000033;//配置为推挽输出
}
