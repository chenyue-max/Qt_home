#include "sht20.h"
#define SHT20_ADDR 0x80
#define SHT20_RT 0xF3
#define SHT20_RH 0xF5

unsigned char sht20_measure(float* Temperature, float* Humidity)
{
	unsigned char temp[2] = {0};
	u16 ST = 0;
	if(!Single_Read_Len(SHT20_ADDR, SHT20_RT, 2, temp))
	{
		ST = (temp[0]<<8)|temp[1];
		ST &= ~0x0003;
		*Temperature = ((float)ST*0.00268127)-46.85;	
	}else{
		*Temperature = 0;
		return 1;
	}
	if(Single_Read_Len(SHT20_ADDR, SHT20_RH, 2, temp))
	{
		ST = (temp[0]<<8)|temp[1];
		ST &= ~0x0003;
		*Humidity = ((float)ST*0.00190735)-6;
	}else{
		*Humidity = 0;
		return 1;
	}
	return 0;

}
