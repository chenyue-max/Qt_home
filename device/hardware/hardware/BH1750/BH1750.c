/*******************************************************
�����ͺţ�BH1750
ͨ�ŷ�ʽ��IIC
�ļ����ܣ���ȡ����ǿ������
������ַ��0XB8
������ֵ���㹫ʽ��
	ʵ��ֵ=����ֵ/(1.2*͸����*�߾���ģʽ2����ֵ)
��ȡ����¶Ȳ���ָ�0XF3(�Ǳ�������)
*******************************************************/
#include "myiic.h"
#include "BH1750.h"
#include "jpstm32_sysclk.h"

#define BH1750_ADDR					0XB8	//������ַ
#define BH1750_PWOFF				0X00	//�ϵ�
#define BH1750_PWON					0X01	//ͨ��
#define BH1750_RESET				0X07	//��λ���ּĴ����е�ֵ
#define BH1750_H_RE_MOD2		0X11 	//�߾���ģʽ2 ������Ϊ0.5
#define BH1750_CMT_H				0X42  //����͸����Ϊ100% ���üĴ�����8λ
#define BH1750_CMT_L				0X65	//����͸����Ϊ100% ���üĴ�����8λ

/*******************************
��������BH1750_Init
�������ܣ���ʼ��BH1750
��������ֵ���ɹ�����0
*******************************/
void BH1750_Init(void)
{
	Sing_Write_ND(BH1750_ADDR, BH1750_PWON);		//ͨ��
	Sing_Write_ND(BH1750_ADDR, BH1750_RESET);		//��λ
	Sing_Write_ND(BH1750_ADDR, BH1750_CMT_H);	
	Sing_Write_ND(BH1750_ADDR, BH1750_CMT_L);			//����͸����Ϊ100%
	Sing_Write_ND(BH1750_ADDR, BH1750_H_RE_MOD2);	//����Ϊ�߾���ģʽ
}	
/*******************************
��������BH1750_Init
�������ܣ���ʼ��BH1750
��������ֵ���ɹ�����0
*******************************/
void BH1750_Start(void)
{
	Sing_Write_ND(BH1750_ADDR, BH1750_PWON);		//ͨ��
	Sing_Write_ND(BH1750_ADDR, BH1750_RESET);		//��λ
	Sing_Write_ND(BH1750_ADDR, BH1750_CMT_H);	
	Sing_Write_ND(BH1750_ADDR, BH1750_CMT_L);			//����͸����Ϊ100%
	Sing_Write_ND(BH1750_ADDR, BH1750_H_RE_MOD2);	//����Ϊ�߾���ģʽ
}	

/*******************************
��������BH1750_Measure
�������ܣ���ȡһ��BH1750�Ĳ���ֵ
��������ֵ���ɹ�����0
ע�⣺ÿ�ζ�ȡ����ǿ����������Ҫ���120ms
			�ڸ߾���ģʽ�´�����ת��һ��������Ҫ����120msʱ��
*******************************/
unsigned char BH1750_Measure(float* Result)
{
	unsigned char temp[2]={0};
	u16 ST = 0;
	if(Sing_Read_NR(BH1750_ADDR, 2, temp))
	 {
		ST = (temp[0]<<8)|temp[1];
		*Result = (u16)ST / 0.6;
	 }
	else
	{
		*Result = 0;
		return 1;
	}
	return 0;
}

/*******************************
��������BH1750_Measure
�������ܣ���ȡһ��BH1750��ԭʼ����ֵ
��������ֵ���ɹ�����0
ע�⣺ÿ�ζ�ȡ����ǿ����������Ҫ���120ms
			�ڸ߾���ģʽ�´�����ת��һ��������Ҫ����120msʱ��
*******************************/
unsigned char BH1750_Original_Measure(u16* Result)
{
	unsigned char temp[2]={0};
//	u16 ST = 0;
	if(Sing_Read_NR(BH1750_ADDR, 2, temp))
	 {
		* Result = (temp[0]<<8)|temp[1];
	 }
	else
	{
		*Result = 0;
		return 1;
	}
	return 0;
}






