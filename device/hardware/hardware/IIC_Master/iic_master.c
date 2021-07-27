#include "iic_master.h"
#include "jpstm32_sysclk.h"

//��ʼ��IIC
void IIC_M_Init(void)
{					     
	RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ��	   	  
	GPIOB->CRL&=0XFFFFFF00;
	GPIOB->CRL|=0X00000033;//PB0/PB1����������� 
	IIC_M_SCL = 1;
	IIC_M_SDA = 1;
}
//����IIC��ʼ�ź�
void IIC_M_Start(void)
{
	//SDA_M_OUT();     //sda�����
	IIC_M_SDA=1;	  	  
	IIC_M_SCL=1;
	delayUs(4);
 	IIC_M_SDA=0;//START:when CLK is high,DATA change form high to low 
	delayUs(4);
	IIC_M_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_M_Stop(void)
{
	SDA_M_OUT();//sda�����
	IIC_M_SCL=0;
	IIC_M_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delayUs(4);
	IIC_M_SCL=1; 
	delayUs(1);
	IIC_M_SDA=1;//����I2C���߽����ź�
	delayUs(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_M_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_M_IN();      //SDA����Ϊ����  
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
	IIC_M_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��		  
void IIC_M_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_M_OUT(); 	    
    IIC_M_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_M_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delayUs(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_M_SCL=1;
		delayUs(2); 
		IIC_M_SCL=0;	
		delayUs(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_M_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_M_IN();//SDA����Ϊ����
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
        IIC_M_NAck();//����nACK
    else
        IIC_M_Ack(); //����ACK   
    return receive;
}
