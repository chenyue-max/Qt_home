/*******************************************************
�����ͺţ�VEMl6070
ͨ�ŷ�ʽ��IIC
�ļ����ܣ���ȡ������ǿ������
������ַ��0X70
����������ǿ�ȶ��ձ�����ѡ��ΪRset=270K��(Ӳ������) IT=4t��
��ֵ											�ȼ�
0~2240				 						 ��
2241~4482									 �е�
4483~5976									 ��
5977~8216                  �ǳ���
>8217											 �����ϣ����ˣ�����Ҫ��
*******************************************************/
#include "myiic.h"
#include "veml6070.h"

#define VEML6070_ADDR	0X70	//������ַ
#define VEML6070_DH		0X73	//���¶�
#define VEML6070_DL		0X71	//��ʪ��
/*******************************
��������VEML6070_Set
�������ܣ���ȡ����������
��������ֵ���ɹ�����0			 
*******************************/
unsigned char VEML6070_Set(void)
{
	IIC_Start();
  IIC_Send_Byte(0X70);
  if (IIC_Wait_Ack()) 
		{
      IIC_Stop();
      return 1;
		}
	IIC_Send_Byte(0X0E);//�˴�ģʽ���ã��ر�ACK���� IT����Ϊ4T
	if (IIC_Wait_Ack()) 
		{
      IIC_Stop();
      return 1;
		}
	IIC_Stop();
	return  0;
}
/*******************************
��������VEML6070_Measure
�������ܣ���ȡ������ǿ��
��������ֵ���ɹ�����0
*******************************/
unsigned char VEML6070_Measure(u16* Result)
{
	u8 tempH,tempL;
	/*********��ȡ��8λ����*********/
	IIC_Start();
  IIC_Send_Byte(0X73);
  if (IIC_Wait_Ack()) 
		{
      IIC_Stop();
      return 1;
		}
	tempH=IIC_Read_Byte(1);//��ȡ��������
	IIC_Stop();
	/*********��ȡ��8λ����*********/
	IIC_Start();
  IIC_Send_Byte(0X71);
  if (IIC_Wait_Ack()) 
		{
      IIC_Stop();
      return 1;
		}
	tempL=IIC_Read_Byte(1);//��ȡ��������
	IIC_Stop();
	*Result = (tempH<<8)|tempL;
	return 0;
}
