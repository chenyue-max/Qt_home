#include "jpstm32_gpio.h"
#include "jpstm32_sysclk.h"
#include "sys.h"


#include "run.h"
#include "ZigBee_usart.h"


extern volatile u8 Usart1_RFinish;
extern u8 Usart1_RBuffer[USART_BUFFER_LEN];


extern volatile u8 ZigbeeR_Finish;
extern u8 zigbee_buffer[ZIGBEE_BUFFER_LEN];

int main()
{
	u8 d_len = 0;
	u8 buf[15] = {0};
	
	sysclkInit(9);
	delayInit(72);
	usart_init(72, 9600);
	zigbee_usart_init(36, 57600);
	JTAG_Set(01);
	
	while(1)
	{
		if(Usart1_RFinish == 1)
		{
			Usart1_RFinish = 0;
			d_len = Usart1_RBuffer[5];
			zigbee_send(d_len, Usart1_RBuffer);
		}
		if(ZigbeeR_Finish == 1)
		{
			ZigbeeR_Finish = 0;
			put_c(13, zigbee_buffer);
		}
		
		
	}
	
}

