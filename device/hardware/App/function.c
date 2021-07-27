
#include "function.h"
u8 receive_data[15]={0};

#if BOARD1

#include "WS2812B.h"
#include "TP4115.h"
u8 led1=0,led2=0,led3=0,led4=0;
void device_init(void)
{
  WS2812B_Init();
  PT4115_Init();
  WS2812B_Clear();

}
void device_control(u8 device_id,u8 *control)
{
  u32 RGB_COLOR;

  switch(device_id)
  {
    case  0x11://led1
      led1=control[0];
      PT4115_Change(led1,led2,led3,led4);
      break;
    
    case  0x12://led2
      led2=control[0];
      PT4115_Change(led1,led2,led3,led4);
      break;
    
    case  0x13://led3
      led3=control[0];
      PT4115_Change(led1,led2,led3,led4);
      break;
    
    case  0x14://led4
      led4=control[0];
      PT4115_Change(led1,led2,led3,led4);
      break;
    
    case  0x15://rgb_led
      RGB_COLOR=control[0]<<16|control[1]<<8|control[2];
      WS2812B_Clear();
      WS2812B_Pixel_EN(0,0,16,&RGB_COLOR,1);
    break;
    
    default:
      break;
  }  
  


}
#endif

#if BOARD2

#include "CO2.h"
#include "BH1750.h"
#include "myiic.h"
#include "SHT20.h"
#include "veml6070.h"


void device_init(void)  
{
  IIC_Init();//??????
  BH1750_Init();
  CO2_Init();
 
  
  
}
void device_control(u8 device_id,u8 *control)
{
  u8 data[4]={0};
  u8 data_len=0;
  u16 s_data;
  float temp = 0, hum = 0;
  switch(device_id)
  {
    case 0x16://CO2
      if(control[0] == 0x01)
      {
        CO2_Measure(&data[0],&data[1]);
        data_len = 2;
        device_feedback(data_len,data,device_id);
      }
      break;
      
    case 0x17://???
      if(control[0] == 0x01)
      {
      VEML6070_Measure(&s_data);//????
      data[0]=s_data>>8;//???????
      data[1]=s_data&0xff;//???????
      data_len = 2;
      device_feedback(data_len,data,device_id);
      }
          
      break;
    case 0x18://??1
      if(control[0] == 0x01)
      {
      SHT20_Measure(&temp,&hum);
      data[0]=temp ;
      data[1]=(temp-data[0])*100;
      data_len=2;
      device_feedback(data_len,data,device_id);
      }
      
      break;
    case 0x19://??1
      if(control[0] == 0x01)
      {
       SHT20_Measure(&temp,&hum);
      data[0]=hum;
      data[1]=(hum-data[0])*100;
      data_len=2;
      device_feedback(data_len,data,device_id);
      }
    
      break;
    case 0x2c://??
      if(control[0] == 0x01)
      {
      BH1750_Measure(&temp);
      data[0]=temp;
      data[1]=(temp-data[0])*100;
      data_len=2;
      device_feedback(data_len,data,device_id);
      }
      
      break;
    default:
      break;
  }
}
#endif
#if BOARD3

#include "security.h"
void device_init(void)
{
  Security_GPIO_Init();
}
void device_control(u8 device_id,u8 *control)
{
  u8 data[1]={0};
  u8 data_len;
  switch(device_id)
  {
    case 0x1a://甲烷
      if(control[0]==0x01)
      {
        if(Methane_Measure==0x01)
          data[0]=0x01;
        else
          data[0]=0x02;
        data_len=1;
        device_feedback(data_len,data,device_id);
      }
      break;
    case 0x1b://火光
      if(control[0]==0x01)
      {
        if(Fire_Measure==0x01)
          data[0]=0x01;
        else
          data[0]=0x02;
        data_len=1;
        device_feedback(data_len,data,device_id);
      }
      break;
    case 0x1c://烟雾
      if(control[0]==0x01)
      {
        if(Smog_Measure==0x01)
          data[0]=0x01;
        else
          data[0]=0x02;
        data_len=1;
        device_feedback(data_len,data,device_id);
      }
      break;
    case 0x1d://人体红外
      if(control[0]==0x01)
      {
        if(Infrared_Measure==0x01)
          data[0]=0x01;
        else
          data[0]=0x02;
        data_len=1;
        device_feedback(data_len,data,device_id);
      }
      break;
    default:
      break;
    
  }
  
}
#endif

#if BOARD4

#include "PM2.5.h"
#include "myiic.h"
#include "sht20.h"


void device_init(void)
{
  IIC_Init();
  PM2_5_Init();
  
}
void device_control(u8 device_id,u8 *control)
{
  u8 data[2]={0};
  float temp,hum;
  u8 data_len=0;
  switch(device_id)
  {
    case 0x1e://PM2.5
      if(control[0]==0x01)
      {
        PM2_5_Measure(&data[0],&data[1]);
        data_len=2;
        device_feedback(data_len,data,device_id);
      }
      
      break;
    case 0x1f://temp2
       if(control[0] == 0x01)
      {
      SHT20_Measure(&temp,&hum);
      data[0]=temp ;
      data[1]=(temp-data[0])*100;
      data_len=2;
      device_feedback(data_len,data,device_id);
      }
      break;
    case 0x20://hum2
      if(control[0] == 0x01)
      {
       SHT20_Measure(&temp,&hum);
      data[0]=hum;
      data[1]=(hum-data[0])*100;
      data_len=2;
      device_feedback(data_len,data,device_id);
      }
      break;
    default:
      break;
  }
}  

#endif


#if BOARD5

#include "security_windows.h"

void device_init(void)
{
  Security_Windows_GPIO_Init();
}
void device_control(u8 device_id,u8 *control)
{
  u8 data[1]={0};
  u8 data_len=0;
  switch(device_id)
  {
    case 0x21://报警器
      if(control[0]==0x01)
        WARN_RING = 1;
      else if(control[0]==0x02)
        WARN_RING = 0;
      break;
    case 0x22://报警灯
      if(control[0]==0x01)
        WARN_LED = 1;
      else if(control[0]==0x02)
        WARN_LED = 0;
      break;
    case 0x23://对射开关
      if(control[0])
      {
        if(RELATIVE_SWITCH==0x01)
          data[0]=0x01;
        else
          data[0]=0x02;
        data_len=1;
        device_feedback(data_len,data,device_id);
        
      }
        
      break;
    case 0x24://反射开关
      if(control[0])
      {
        if(PHOTO_SWITCH==0x01)
          data[0]=0x01;
        else
          data[0]=0x02;
        data_len=1;
        device_feedback(data_len,data,device_id);
        
      }
      break;
  }
}
#endif


#if BOARD6
void device_init(void);
void device_control(u8 *control);
#endif

#if BOARD7
#include "A4988.h"
#include "fan.h"
#include "Relay.h"
void device_init(void)
{
	A4988_Init();
	Fan_Gpio_Init();
	Relay_Gpio_Init();
}
void device_control(u8 device_id,u8 *control)
{
	switch(device_id)
	{
		case 0x26://步进电机
			if(control[0]==0x01)
			{
				A4988_DIR=1;
				Motor_Control(2000,380);
			}
			else if(control[0]==0x02)
			{
				A4988_DIR=0;
				Motor_Control(2000,380);
			}
			break;
		case 0x27://风扇
			if(control[0]==0x01)
			{
				FAN_Set=1;
			}
			else if(control[0]==0x02)
			{
				FAN_Set=0;
			}
			break;
		case 0x28://继电器
		if(control[0]==0x01)
		{
			Relay1_Set=1;
		}else if(control[0]==0x02)
		{
			Relay1_Set=0;
		}
			break;
		case 0x29:
		if(control[0]==0x01)
		{
			Relay2_Set=1;
		}else if(control[0]==0x02)
		{
			Relay2_Set=0;
		}
			break;

	}
}
#endif

#if BOARD8
#include "lock.h"
void device_init(void)
{
	Lock_Init();
}
void device_control(u8 device_id,u8 *control)
{
	if(device_id==0x2A)
	{
		if(control[0]==0x01)
			LOCK_CONTROL=1;
		else if(control[0]==0x02)
			LOCK_CONTROL=0;
	}
}
#endif


void device_feedback(u8 data_len,u8 *data,u8 device_id)
{
	u8 i;
	receive_data[0]=0xEF;
	receive_data[1]=0xEF;
	receive_data[2]=0x00;
	receive_data[3]=0xFF;
	receive_data[4]=0xFF;
	receive_data[5]=data_len+9;
	receive_data[6]=NODE_ID;
  receive_data[7]=device_id;
  for(i=0;i<data_len;i++)
	{
		receive_data[8+i]=data[i];
		
	}
	receive_data[data_len+8]=0x0F;
	zigbee_send(data_len+9,receive_data);
	
	
}

void analysis(void)
{
  u8 device_id;
  u8 control[3]={0};
  u8 c_len,i,all_len=0,x=0;
  
  if(zigbee_buffer[0]==0xFE&&zigbee_buffer[1]==0xFE)
  {
			all_len=zigbee_buffer[2];//获取数据总长度
	     while(all_len)
		 {
			 if(zigbee_buffer[0+x]==0xFE&&zigbee_buffer[1+x]==0xFE)
			 {
					if(zigbee_buffer[6+x]==NODE_ID)
				{
					device_id=zigbee_buffer[7+x];
					c_len=zigbee_buffer[5+x]-9;
					for(i=0;i<c_len;i++)
					{
						control[0]=zigbee_buffer[8+i+x];		}
						device_control(device_id,control);
						x=c_len+9;
						all_len-=x;
			

			}else{
					break;
				}
		 }
   
	 }
  }
}

