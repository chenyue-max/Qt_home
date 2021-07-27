#include "PM2.5.h"
#include "usart3.h"

extern u8 Usart3Buffer[15];

//初始化PM2.5传感器
void PM2_5_Init()
{
	usart3_init(36, 9600);
}
//获取传感器数据值
void PM2_5_Measure(u8* PM25_D_H, u8* PM25_D_L)
{
	*PM25_D_H = Usart3Buffer[3];
	*PM25_D_L = Usart3Buffer[2];
}


