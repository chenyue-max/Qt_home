#include "function.h"
#include "Tim1.h"
int main()
{
//  u8 control[10];
  sysclkInit(9);
  delayInit(72);
		JTAG_Set(01);
  zigbee_usart_init(36,57600);
  device_init();
	//如果需心跳包
//	TIM1_Init(TIME_h,7200);
  while(1)
  {
    if(ZigbeeR_Finish==1)
    {
      ZigbeeR_Finish=0;
      analysis();
    }
  }
    
  
}









  


