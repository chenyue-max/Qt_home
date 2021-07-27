/* * 
 * 自定义GUI底层接口实现
 * */

#include "briupFontDraw.h"
#include "briupLCD.h"
#include "ff.h"
//中文字体路径
const TCHAR GBK16_PATH[] = "0:/system/font/GBK16.FON";
const TCHAR GBK32_PATH[] = "0:/system/font/GBK32.FON";

//const TCHAR GBK16_PATH[] = "0:/font/GBK16.FON";
//const TCHAR GBK32_PATH[] = "0:/font/GBK32.FON";
//GUI结构
_briupFont_base	briupFontBase;


//初始化GUI
void	briupFontInit(void)
{
	//u8	ret;
	briupFontBase.bgcolor = GUI_COLOR_WHITE;
	briupFontBase.fgcolor = GUI_COLOR_BLACK;
	briupFontBase.font = GUI_FONT_32;
	f_open(&briupFontBase.f16 , GBK16_PATH, FA_READ);
	f_open(&briupFontBase.f32 , GBK32_PATH, FA_READ);
}

//绘制字体
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
//绘制中文
u8	briupFontDrawGbkFont(u16 left, u16 top, u8* gbk, u16 color, GUI_FONT briupFontFont)
{
	u32 	foffset;//点阵库在文件中的偏移量
	UINT	ret;//保存f_read()的返回值
	//FIL		fp;//文件指针，指向字库文件
	u16		byte_n = 0;//表示当前文字所用字节数
	u16		y0 = top;//垂直坐标的回写值
	u8		font_h, font_l;//汉字编码的高、低字节
	u8		byte, bit;
	u8		temp;
	u8		f_buf[129];//保存当前汉字的点阵数组

	//计算点阵偏移量
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
	//计算当前字号对应点阵所用的字节数
	byte_n = briupFontFont*briupFontFont/8;
	//计算当前汉子在点阵库中的偏移位置
	foffset = (u32)(((u32)font_h*190+(u32)font_l))*byte_n;
	//读取对应汉字的点阵信息

	switch(briupFontFont)
	{
		case GUI_FONT_16:	
			//seek归零
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
	
	//根据点阵内容绘制汉字
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

//获取背景颜色
u16		briupFontGetBGColor()
{
	return briupFontBase.bgcolor;
}











