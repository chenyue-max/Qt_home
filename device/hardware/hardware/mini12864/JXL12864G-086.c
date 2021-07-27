/*************************************************************
 * File name	: JXL12864G-086.c
 * Author			: Bradley_Ozing
 * Version		:
 * Date				: 2016-1
 * Description: JXL12864G-086(���ֿ�)��ʾ��ʵ���ļ�
 * Copyright @ 2013 by Briup Technology,Inc. All rights Reserved.
 *
 * Includes		:
 *	> ��ӡ 5*8 ��С���ַ��� ---> Display_String_5x8(u8 page,u8 column,u8 *text)
 *  > ��ӡ GB2312 ���ַ��� ----> Display_GB2312_String(u8 page,u8 column,u8 *text)
 *	>	ȫ������		-------------->	Clear_Screen(void);
 *************************************************************/
 #include "JXL12864G-086.h"

long fontaddr_IN=0;


//ȫ������
void Clear_Screen_IN()
{
 unsigned char i,j;
 for(i=0;i<9;i++)
 {
 Transfer_Cmd_Lcd_IN(0xb0+i);
 Transfer_Cmd_Lcd_IN(0x10);
 Transfer_Cmd_Lcd_IN(0x00);
 for(j=0;j<132;j++)
 {
 Transfer_Data_Lcd_IN(0x00);
 }
 }
}

//��ӡGB2312���ַ���
void Display_GB2312_String_IN(u8 page,u8 column,u8 *text)
{
	u8 i= 0;
	//fontaddr_IN=0;
	while((text[i]>0x00))
	{
		
		if(((text[i]>=0xb0) &&(text[i]<=0xf7))&&(text[i+1]>=0xa1))
			{
				//������壨GB2312�������ھ���Ѷ�ֿ� IC �еĵ�ַ�����¹�ʽ�����㣺
				//Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0
				//���ڵ��� 8 λ��Ƭ���г˷�������⣬���Է�����ȡ��ַ
				fontaddr_IN = (text[i]- 0xb0)*94;
				fontaddr_IN += (text[i+1]-0xa1)+846;
				fontaddr_IN = (long)(fontaddr_IN*32);
				get_and_write_16x16_IN(fontaddr_IN,page,column) ; //��ָ����ַ��������д��Һ����ָ����page,column)������
				i+=2;
				column+=16;
			}
		else if(((text[i]>=0xa1) &&(text[i]<=0xa3))&&(text[i+1]>=0xa1 ))
			{
				//������壨GB2312��15x16 ����ַ��ھ���Ѷ�ֿ� IC �еĵ�ַ�����¹�ʽ�����㣺
				//Address = ((MSB - 0xa1) * 94 + (LSB - 0xA1))*32+ BaseAdd;BaseAdd=0
				//���ڵ��� 8 λ��Ƭ���г˷�������⣬���Է�����ȡ��ַ
				fontaddr_IN = (text[i]- 0xa1)*94;
				fontaddr_IN += (text[i+1]-0xa1);
				fontaddr_IN = (long)(fontaddr_IN*32);
				get_and_write_16x16_IN(fontaddr_IN,page,column) ; //��ָ����ַ��������д��Һ����ָ����page,column)������
				i+=2;
				column+=16;
			}
		 else if((text[i]>=0x20) &&(text[i]<=0x7e))
		 {	 
				 fontaddr_IN = (text[i]- 0x20);
				 fontaddr_IN = (unsigned long)(fontaddr_IN*16);
				 fontaddr_IN = (unsigned long)(fontaddr_IN+0x3cf80);
				 get_and_write_8x16_IN(fontaddr_IN,page,column); //��ָ����ַ��������д��Һ����ָ����page,column)������
				 i+=1;
				 column+=8;
		 }
		else
		 i++;
	}
}


//дָ� LCD ģ��
void Transfer_Cmd_Lcd_IN(int cmd)
{
	 u8 i;
	 Lcd_CS_IN = 0;
	 Lcd_RS_IN = 0;
	 for(i=0;i<8;i++)
		 {
			 Lcd_Sclk_IN=0;
			 delayUs(10); //��������ʱ
			 if(cmd&0x80) 
					Lcd_Sid_IN=1;
			 else 
				  Lcd_Sid_IN=0;
			 Lcd_Sclk_IN=1;
			 delayUs(10); //��������ʱ
			 cmd = cmd<<=1;
		 }
	 Lcd_CS_IN=1;
}


//д���ݵ� LCD ģ��
void Transfer_Data_Lcd_IN(int data)
{
	 char i;

	 Lcd_CS_IN = 0;
	 Lcd_RS_IN = 1;
	 for(i=0;i<8;i++)
	 {
			Lcd_Sclk_IN=0;
			if(data&0x80) Lcd_Sid_IN=1;
			else Lcd_Sid_IN=0;
			Lcd_Sclk_IN=1;
			data = data<<1;
		}
	 Lcd_CS_IN=1;
}


//LCDģ��GPIO�ڳ�ʼ��
void Lcd_GPIO_Iint_IN()
{
	RCC->APB2ENR |= 1<<3;//ʹ��PORTBʱ��
	GPIOB->CRL&=0X0000FFFF;
	GPIOB->CRL|=0X83330000;//PB4 5 6 ������� 7����  
	GPIOB->CRH&=0X0000FFF0;
	GPIOB->CRH|=0X33330003;//PB8 12 13 14 15�������
}



//LCD ģ���ʼ��
void Lcd_Init_IN()
{
	 Lcd_GPIO_Iint_IN();//GPIO�ڳ�ʼ��
	
	 Lcd_Reset_IN=0;  //�͵�ƽ��λ
	 delayMs(100);
	 Lcd_Reset_IN=1 ; //��λ���
	 delayMs(100);
	 Transfer_Cmd_Lcd_IN(0xe2); //��λ
	 delayMs(5);
	 Transfer_Cmd_Lcd_IN(0x2c); //��ѹ���� 1
	 delayMs(50);
	 Transfer_Cmd_Lcd_IN(0x2e); //��ѹ���� 2
	 delayMs(50);
	 Transfer_Cmd_Lcd_IN(0x2f); //��ѹ���� 3
	 delayMs(5);
	 Transfer_Cmd_Lcd_IN(0x23);  //�ֵ��Աȶȣ������÷�Χ 0x20��0x27
	 Transfer_Cmd_Lcd_IN(0x81);  //΢���Աȶ�
	 Transfer_Cmd_Lcd_IN(0x28); //΢���Աȶȵ�ֵ�������÷�Χ 0x00��0x3f
	 Transfer_Cmd_Lcd_IN(0xa2);  //1/9 ƫѹ�ȣ�bias��
	 Transfer_Cmd_Lcd_IN(0xc8);  //��ɨ��˳�򣺴��ϵ���
	 Transfer_Cmd_Lcd_IN(0xa0);  //��ɨ��˳�򣺴�����
	 Transfer_Cmd_Lcd_IN(0x40);  //��ʼ�У���һ�п�ʼ
	 Transfer_Cmd_Lcd_IN(0xaf);  //����ʾ
}


void Lcd_Address(u32 page,u32 column)
{
 column=column-0x01;
 Transfer_Cmd_Lcd_IN(0xb0+page-1); //����ҳ��ַ��ÿ 8 ��Ϊһҳ��ȫ���� 64 �У����ֳ� 8 ҳ
 Transfer_Cmd_Lcd_IN(0x10+(column>>4&0x0f)); //�����е�ַ�ĸ� 4 λ
 Transfer_Cmd_Lcd_IN(column&0x0f); //�����е�ַ�ĵ� 4 λ
}


//��ʾ 128x64 ����ͼ��
void display_128x64_IN(u8 *dp)
{
 u32 i,j;
 for(j=0;j<8;j++)
 {
 Lcd_Address(j+1,1);
 for (i=0;i<128;i++)
 {
 Transfer_Data_Lcd_IN(*dp); //д���ݵ� LCD,ÿд��һ�� 8 λ�����ݺ��е�ַ�Զ��� 1
 dp++;
 }
 }
}



//��ָ�����Ѷ�ֿ� IC
void send_command_to_ROM_IN( u8 datu )
{
 u8 i;
 for(i=0;i<8;i++ )
 {
 Rom_SCK_IN=0;
 delayUs(10);
 if(datu&0x80)Rom_IN_IN = 1;
 else Rom_IN_IN = 0;
 datu = datu<<1;
 Rom_SCK_IN=1;
 delayUs(10);
 }
}


//�Ӿ���Ѷ�ֿ� IC ��ȡ���ֻ��ַ����ݣ�1 ���ֽڣ�
static u8 get_data_from_ROM_IN()
{
 u8 i;
 u8 ret_data=0;
 for(i=0;i<8;i++)
 {
 Rom_OUT_IN=1;
 Rom_SCK_IN=0;
 delayUs(1);
 ret_data=ret_data<<1;
 if( Rom_OUT_IN )
 ret_data=ret_data+1;
 else
 ret_data=ret_data+0;
 Rom_SCK_IN=1;
 delayUs(1);
 }
 return(ret_data);
}


//��ָ����ַ��������д��Һ����ָ����page, column)������
void get_and_write_16x16_IN(long fontaddr_IN,u8 page,u8 column)
{
 u8 i,j,disp_data;
 Rom_CS_IN = 0;
 send_command_to_ROM_IN(0x03);
 send_command_to_ROM_IN((fontaddr_IN&0xff0000)>>16); //��ַ�ĸ� 8 λ,�� 24 λ
 send_command_to_ROM_IN((fontaddr_IN&0xff00)>>8) ; //��ַ���� 8 λ,�� 24 λ
 send_command_to_ROM_IN(fontaddr_IN&0xff); //��ַ�ĵ� 8 λ,�� 24 λ
 for(j=0;j<2;j++)
 {
 Lcd_Address(page+j,column);
 for(i=0; i<16; i++ )
 {
 disp_data=get_data_from_ROM_IN();
 Transfer_Data_Lcd_IN(disp_data); //д���ݵ� LCD,ÿд�� 1 �ֽڵ����ݺ��е�ַ�Զ��� 1
 }
 }
 Rom_CS_IN=1;
}


//��ָ����ַ��������д��Һ����ָ����page, column)������
void get_and_write_8x16_IN(long fontaddr_IN,u8 page,u8 column)
{
 u8 i,j,disp_data;
 Rom_CS_IN = 0;
 send_command_to_ROM_IN(0x03);
 send_command_to_ROM_IN((fontaddr_IN&0xff0000)>>16); //��ַ�ĸ� 8 λ,�� 24 λ
 send_command_to_ROM_IN((fontaddr_IN&0xff00)>>8) ; //��ַ���� 8 λ,�� 24 λ
 send_command_to_ROM_IN(fontaddr_IN&0xff); //��ַ�ĵ� 8 λ,�� 24 λ
 for(j=0;j<2;j++)

 {
 Lcd_Address(page+j,column);
 for(i=0; i<8; i++ )
 {
 disp_data=get_data_from_ROM_IN();
 Transfer_Data_Lcd_IN(disp_data); //д���ݵ� LCD,ÿд�� 1 �ֽڵ����ݺ��е�ַ�Զ��� 1
 }
 }
 Rom_CS_IN=1;
}


