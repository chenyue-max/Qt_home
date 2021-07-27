/*************************************************************
 * File name	: JXL12864G-086.h
 * Author			: Bradley_Ozing�������壩
 * Version		:
 * Date				: 2016-1
 * Description: JXL12864G-086(���ֿ�)��ʾ������ͷ�ļ�
 * Copyright @ 2013 by Briup Technology,Inc. All rights Reserved.
 *
 * Includes		:
 *  > ��ӡ GB2312 ���ַ��� ----> Display_GB2312_String(u8 page,u8 column,u8 *text)
 *	>	ȫ������		-------------->	Clear_Screen(void);
 *************************************************************/
#ifndef	__JXL12864G_086_H__
#define	__JXL12864G_086_H__

#include "jpstm32_gpio.h"
#include "jpstm32_sysclk.h"



#define Lcd_Sclk_IN			PBxOut(14) 			//�ӿڶ���:Lcd_Sclk ���� LCD �� SCLK
#define Lcd_Sid_IN 			PBxOut(13)				//�ӿڶ���:Lcd_Sid ���� LCD �� SDA
#define Lcd_RS_IN				PBxOut(12)			//�ӿڶ���:Lcd_RS ���� LCD �� RS,Ҳ�С�CD��
#define Lcd_CS_IN				PBxOut(15) 			//�ӿڶ���:Lcd_CS ���� LCD �� CS1
#define Lcd_Reset_IN		PBxOut(8)				//�ӿڶ���:Lcd_Reset ���� LCD �� RESET
#define Rom_IN_IN				PBxOut(6) 			//�ֿ� IC �ӿڶ���:Rom_IN �����ֿ� IC �� SI
#define Rom_OUT_IN			PBxIn(7)  		  //�ֿ� IC �ӿڶ���:Rom_OUT �����ֿ� IC �� SO
#define Rom_SCK_IN			PBxOut(4)  		//�ֿ� IC �ӿڶ���:Rom_SCK �����ֿ� IC �� SCK
#define Rom_CS_IN				PBxOut(5)			//�ֿ� IC �ӿڶ��� Rom_CS �����ֿ� IC �� CS

//=====================================================================================
//
//	�����ʾ����������
//
//=====================================================================================


//��ӡGB2312���ַ���
void Display_GB2312_String_IN(u8 page,u8 column,u8 *text);
//ȫ������
void Clear_Screen_IN(void);

//LCDģ��GPIO�ڳ�ʼ��
void Lcd_GPIO_Iint_IN(void);
//LCD ģ���ʼ��
void Lcd_Init_IN(void);
//дָ�LCD ģ��
void Transfer_Cmd_Lcd_IN(int cmd);
//д���ݵ� LCD ģ��
void Transfer_Data_Lcd_IN(int data);
//LCD ���ݵ�ַ����
void Lcd_Address_IN(u32 page,u32 column);
//��ʾ 128x64 ����ͼ��
void display_128x64_IN(u8 *dp);




//��ָ�����Ѷ�ֿ� IC
void send_command_to_ROM_IN( u8 datu );
//�Ӿ���Ѷ�ֿ� IC ��ȡ���ֻ��ַ����ݣ�1 ���ֽڣ�
static u8 get_data_from_ROM_IN(void);
//��ָ����ַ��������д��Һ����ָ����page, column)������
void get_and_write_16x16_IN(long fontaddr,u8 page,u8 column);
//��ָ����ַ��������д��Һ����ָ����page, column)������
void get_and_write_8x16_IN(long fontaddr,u8 page,u8 column);




#endif

