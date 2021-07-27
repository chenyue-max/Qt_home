/* * 
 * �Զ���GUI�ײ�ӿ�ʵ��
 * */

#include "briupFontDraw.h"
#include "briupLCD.h"
#include "ff.h"
//��������·��
const TCHAR GBK16_PATH[] = "0:/system/font/GBK16.FON";
const TCHAR GBK32_PATH[] = "0:/system/font/GBK32.FON";

//const TCHAR GBK16_PATH[] = "0:/font/GBK16.FON";
//const TCHAR GBK32_PATH[] = "0:/font/GBK32.FON";
//GUI�ṹ
_briupFont_base	briupFontBase;


//��ʼ��GUI
void	briupFontInit(void)
{
	//u8	ret;
	briupFontBase.bgcolor = GUI_COLOR_WHITE;
	briupFontBase.fgcolor = GUI_COLOR_BLACK;
	briupFontBase.font = GUI_FONT_32;
	f_open(&briupFontBase.f16 , GBK16_PATH, FA_READ);
	f_open(&briupFontBase.f32 , GBK32_PATH, FA_READ);
}

//��������
void	briupFontDrawText(u16 x, u16 y, u8* str, u16 color, u16 bg_color, GUI_FONT font)
{
	u8 inc = 0;
	u8 * temp = str;
	switch(font){
		case GUI_FONT_16:
			inc = 16;
			break;
		case GUI_FONT_32:
			inc = 32;
			break;
		default:
			return;
	}
	
	while(*temp){
		if(GUI_SCREEN_IS_HOR){
			if(*temp>=0x81){
				if(briupFontDrawGbkFont(x, y, temp, color, font))
				{
					return;
				}
				if(GUI_FONT_32 == inc){
					x += (inc-5);
				} else {
					x += inc+1;
				}
				temp += 2;
			}else{
				briupLcdShowChar(x, y, *temp, font, 1, color, bg_color);
				x += inc/2;	
				temp += 1;
			}
		}else{
			if(*temp>=0x81)
			{
				if(briupFontDrawGbkFont(x, y, temp, color, font))
				{
					return;
				}
				temp += 2;
			}
			else{
				briupLcdShowChar(x, y, *temp, font, 1, color, bg_color);
				temp += 1;
			}
			y += inc;
		}
	}
}
//��������
u8	briupFontDrawGbkFont(u16 left, u16 top, u8* gbk, u16 color, GUI_FONT briupFontFont)
{
	u32 	foffset;//��������ļ��е�ƫ����
	UINT	ret;//����f_read()�ķ���ֵ
	//FIL		fp;//�ļ�ָ�룬ָ���ֿ��ļ�
	u16		byte_n = 0;//��ʾ��ǰ���������ֽ���
	u16		y0 = top;//��ֱ����Ļ�дֵ
	u8		font_h, font_l;//���ֱ���ĸߡ����ֽ�
	u8		byte, bit;
	u8		temp;
	u8		f_buf[129];//���浱ǰ���ֵĵ�������

	//�������ƫ����
	font_h = *gbk;
	font_l = *(++gbk);
	if(font_l<0x7F)
	{
		font_l -= 0x40;
	}
	else 
	{
		font_l -= 0x41;
	}
	font_h -= 0x81;	
	//���㵱ǰ�ֺŶ�Ӧ�������õ��ֽ���
	byte_n = briupFontFont*briupFontFont/8;
	//���㵱ǰ�����ڵ�����е�ƫ��λ��
	foffset = (u32)(((u32)font_h*190+(u32)font_l))*byte_n;
	//��ȡ��Ӧ���ֵĵ�����Ϣ

	switch(briupFontFont)
	{
		case GUI_FONT_16:	
			//seek����
			f_lseek(&briupFontBase.f16, 0);
			f_lseek(&briupFontBase.f16, foffset);
			f_read(&briupFontBase.f16, f_buf, byte_n, &ret);
			break;
		case GUI_FONT_32:
			f_lseek(&briupFontBase.f32, 0);
			f_lseek(&briupFontBase.f32, foffset);
			f_read(&briupFontBase.f32, f_buf, byte_n, &ret);
			break;
		default:
			
			return 1;
	}
	
	//���ݵ������ݻ��ƺ���
	for(byte=0; byte<byte_n; byte++)
	{
		temp = f_buf[byte];
		for(bit=0; bit<8; bit++)
		{
			if(temp&0x80)
			{
				briupLcdFastDrawPoint(left, top, color);
			}
			temp<<=1;
			top++;
			if(top>GUI_SCREEN_HEIGHT)
			{
				return 1;
			}
		}		
		if((top-y0)==briupFontFont)
		{
			top = y0;
			left++;
			if(left>GUI_SCREEN_WIDTH)
			{
				return 1;
			}
		}
	}
	return 0;
}

//��ȡ������ɫ
u16		briupFontGetBGColor()
{
	return briupFontBase.bgcolor;
}











