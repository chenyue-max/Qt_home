#include "iic_master.h"
#include "jpstm32_sysclk.h"

//初始化IIC
void IIC_M_Init(void)
{					     
	RCC->APB2ENR|=1<<3;    //使能PORTB时钟	   	  
	GPIOB->CRL&=0XFFFFFF00;
	GPIOB->CRL|=0X00000033;//PB0/PB1设置推挽输出 
	IIC_M_SCL = 1;
	IIC_M_SDA = 1;
}
//产生IIC起始信号
void IIC_M_Start(void)
{
	//SDA_M_OUT();     //sda线输出
	IIC_M_SDA=1;	  	  
	IIC_M_SCL=1;
	delayUs(4);
 	IIC_M_SDA=0;//START:when CLK is high,DATA change form high to low 
	delayUs(4);
	IIC_M_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_M_Stop(void)
{
	SDA_M_OUT();//sda线输出
	IIC_M_SCL=0;
	IIC_M_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delayUs(4);
	IIC_M_SCL=1; 
	delayUs(1);
	IIC_M_SDA=1;//发送I2C总线结束信号
	delayUs(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_M_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_M_IN();      //SDA设置为输入  
	IIC_M_SDA=1;delayUs(1);	   
	IIC_M_SCL=1;delayUs(1);	
	while(READ_M_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			//IIC_Stop();
			return 1;
		}
	}
	IIC_M_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_M_Ack(void)
{
	IIC_M_SCL=0;
	SDA_M_OUT();
	IIC_M_SDA=0;
	delayUs(2);
	IIC_M_SCL=1;
	delayUs(2);
	IIC_M_SCL=0;
}
//不产生ACK应答		    
void IIC_M_NAck(void)
{
	IIC_M_SCL=0;
	SDA_M_OUT();
	IIC_M_SDA=1;
	delayUs(2);
	IIC_M_SCL=1;
	delayUs(2);
	IIC_M_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答		  
void IIC_M_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_M_OUT(); 	    
    IIC_M_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_M_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delayUs(2);   //对TEA5767这三个延时都是必须的
		IIC_M_SCL=1;
		delayUs(2); 
		IIC_M_SCL=0;	
		delayUs(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_M_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_M_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_M_SCL=0; 
        delayUs(2);
				IIC_M_SCL=1;
        receive<<=1;
        if(READ_M_SDA)receive++;   
				delayUs(1); 
    }	
    if (!ack)
        IIC_M_NAck();//发送nACK
    else
        IIC_M_Ack(); //发送ACK   
    return receive;
}
