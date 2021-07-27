#include "PM2_5.h"
#include "usart3.h"

extern u8 Usart3Buffer[15];

void pm2_5_init(void)
{
	usart3_init(36, 9600);
}
void pm2_5_measure(u8* pm25DH, u8* pm25DL)
{
	*pm25DH = Usart3Buffer[3];
	*pm25DL = Usart3Buffer[2];
}



