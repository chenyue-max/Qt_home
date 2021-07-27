#include "run.h"

extern u8 zigbee_buffer[ZIGBEE_BUFFER_LEN];
u8 res_buffer[11] = {0}; //反馈数组
u8 res_len = 0; //反馈的数据长度


#if board1
#include "beep.h"
#include "rgb_led.h"
#include "ws2812b.h"
#include "tp4115.h"

void interface_init(void)
{
	//初始化
	ws2812b_init();
	tp4115_init();
}
void run(u8 device_id, u8* c_con)
{
	u32 color;
	u8 len,x,y;
	switch (device_id)
	{
		case 0x01:
		tp4115_change(0,c_con[0],0,0);
		break;
		case 0x02:
		tp4115_change(0,0,c_con[0],0);
		break;
		case 0x03:
		tp4115_change(0,0,0,c_con[0]);
		break;
		case 0x04:
		x = c_con[0];
		y = c_con[1];
		len = c_con[2];
		color = c_con[3]<<16|c_con[4]<<8|c_con[5];
		ws2812b_pixel_en(x,y,len,&color,0);
		break;
		default:
		break;
	}
}

#endif

#if board2

#include "myiic.h"
#include "bh1750.h"
#include "jpstm32_sysclk.h"
#include "sht20.h"
#include "vml6070.h"
#include "CO2.h"

void interface_init(void)
{
	IIC_Init();
	bh1750_init();
	CO2_Init();
}

void run(u8 device_id, u8* c_con)
{
	float temp, hum;
	u16 s = 0;
	u8 value[2] = {0};

	switch(device_id)
	{
		case 0x05://co2
		break;
		case 0x06://温度
		sht20_measure(&temp, &hum);
		value[0] = temp;
		value[1] = (temp-value[0])*256;
		res_len = 2;
		response(device_id, value);

		break;
		case 0x07://湿度
		break;
		case 0x08://光照强度
		break;
		case 0x09://紫外线
		break;
		default:
		break;
	}
	
	while(1)
	{
		sht20_measure(&temp, &hum);
		value[0] = temp;
		value[1] = (temp-value[0])*256;
		put_c(2, value);
		
		delayMs(800);
		delayMs(800);

		vml6070_measure(&s);
		value[0] = s>>8;
		value[1] = s&0xFF;
		put_c(2, value);

		delayMs(800);
		delayMs(800);
	}
	
}

#endif

#if board3
#include "security.h"
#include "rgb_led.h"
#include "jpstm32_sysclk.h"

void interface_init(void)
{
	security_gpio_init();
	rgb_led_init();
}
void run(void)
{
	u8 value[8] = {0};
	while(1)
	{
		value[0] = 0x01;
		value[1] = Fire;
		value[2] = 0x20;
		value[3] = Methane;
		value[4] = 0x30;
		value[5] = Smong;
		value[6] = 0x40;
		value[7] = Infrared?0:1;
		put_c(8, value);
		delayMs(800);
		delayMs(800);
	}
}

#endif

#if board4

#include "pm2_5.h"
#include "jpstm32_sysclk.h"

void interface_init(void)
{
	pm2_5_init();	
}
void run(void)
{
	u8 value[2] = {0};
	while(1)
	{
		pm2_5_measure(value, value+1);
		put_c(2, value);
		delayMs(800);
		delayMs(800);
	}
	
}

#endif

#if board5

#include "security5.h"
#include "jpstm32_sysclk.h"

void interface_init(void)
{
	security5_init();
}
void run(void)
{
	u8 value[4] = {0};
	
	while(1)
	{
		WARN_BEEP = 1;
		WARN_LED = 1;
		
		value[0] = 0x10;
		value[1] = PHOTO_SWITCH;//¶ÔÉä¿ª¹ØµÄ×´Ì¬
		value[2] = 0x20;
		value[3] = RELATIVE_SWITCH;//·´Éä¿ª¹Ø
		
		put_c(4, value);
		
		delayMs(800);
		delayMs(800);
		
	}
}

#endif

#if board6
#include "servo.h"
#include "jpstm32_sysclk.h"

void interface_init(void)
{
	servo_init(20000 ,72);//2ms
}
void run(void)
{
	while(1)
	{
	}
	
//		servo_on();
//		delayMs(500);
//		servo_off();
//		delayMs(500);
}

#endif

#if board7

#include "fan.h"
#include "relay.h"
#include "jpstm32_sysclk.h"
#include "a4988.h"

void interface_init(void)
{
	fan_init();
	relay_init();
	a4988_init();
	A4988_DIR = 1;
	motor_control(2000, 380);
}
void run(void)
{
	while(1)
	{
//		Fan_Set = 1;
////		Relay1_Set = 1;
////		Relay2_Set = 1;
//		A4988_DIR = 1;
//		Motor_Control(2000, 386);
//		delayMs(800);
//		delayMs(800);
//		Fan_Set = 0;
////		Relay1_Set = 0;
////		Relay2_Set = 0;

//		A4988_DIR = 0;
//		Motor_Control(2000, 386);
//		delayMs(800);
//		delayMs(800);

	}
	
}

#endif

#if board8

#include "lock.h"
#include "jpstm32_sysclk.h"

void interface_init(void)
{
	lock_init();
}
void run(void)
{
	while(1)
	{
		LOCK = 1;
		delayMs(100);
		LOCK = 0;
		delayMs(100);
	}
}

#endif



//解析函数
void analysis(void)
{
	u8 c_buffer[10] = {0};
	u8 c_len = 0, i = 0;
	u8 a_len = 0;

	if(zigbee_buffer[0] == 0xFE && zigbee_buffer[1] == 0xFE)
	{
		if(zigbee_buffer[zigbee_buffer[2]-1] == 0xFF)
		{
			a_len = zigbee_buffer[2];
			while(a_len)
			{
				//完整的数据
				if(zigbee_buffer[6+c_len] == BoxID)
				{
					//当前箱子的设备
					
					for(i=0;i<(zigbee_buffer[5+c_len]-9);i++)
					{
						c_buffer[i] = zigbee_buffer[8+i+c_len];
					}
					run(zigbee_buffer[7+c_len], c_buffer);

					c_len = zigbee_buffer[5+c_len];
				}else{
					c_len = zigbee_buffer[5+c_len];
				}
				a_len -= c_len;
			}
			
		}else{
			return ;
		}

	}else{
		return ;
	}


}



//数据反馈

void response(u8 device_id, u8 *buf)
{
	u8 i;
	res_buffer[0] = 0xEF;
	res_buffer[1] = 0xEF;
	res_buffer[2] = 0x00;
	res_buffer[3] = 0xFF;
	res_buffer[4] = 0xFF;
	res_buffer[5] = res_len+9;
	res_buffer[6] = BoxID;
	res_buffer[7] = device_id;
	res_buffer[res_len+8] = 0xFF;
	for(i=0;i<res_len;i++)
	{
		res_buffer[8+i] = buf[i];
	}
	zigbee_send(res_len+9, res_buffer);
}


