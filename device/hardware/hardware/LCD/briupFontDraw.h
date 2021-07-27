/* * 
 * 自定义GUI底层接口实定义
 * */
#ifndef __JPSTM32_GUI_H__
#define __JPSTM32_GUI_H__

#include "jpstm32_gpio.h"
#include "jpstm32_nvic.h"
#include "jpstm32_sysclk.h"
#include "sys.h"
#include "ff.h"


//屏幕尺寸与方向
#define		GUI_SCREEN_IS_HOR		1 //屏幕方向，1 横屏，0竖屏
#if		GUI_SCREEN_IS_HOR
	#define		GUI_SCREEN_WIDTH				480
	#define		GUI_SCREEN_HEIGHT			320
#else
	#define		GUI_SCREEN_WIDTH				320
	#define		GUI_SCREEN_HEIGHT			480
#endif

//基本颜色定义
#define		GUI_COLOR_BLACK				0x0000
#define		GUI_COLOR_WHITE				0xFFFF
#define		GUI_COLOR_BLUE       	0xF800 
#define		GUI_COLOR_LBLUE				0xF01F
#define		GUI_COLOR_BRED        0XF81F
#define		GUI_COLOR_GRED 				0XFFE0
#define		GUI_COLOR_RED         0x001F
#define		GUI_COLOR_MAGENTA     0xF81F
#define		GUI_COLOR_GREEN       0x07E0
#define		GUI_COLOR_CYAN        0x7FFF
#define		GUI_COLOR_YELLOW      0x07FF
#define		GUI_COLOR_BROWN 			0XBC40 
#define		GUI_COLOR_BRRED 			0XFC07 
#define		GUI_COLOR_GRAY  			0X8430
//字体定义
typedef enum{
	GUI_FONT_16=16, 
	GUI_FONT_32=32
}GUI_FONT;
//briupFont基本操作
typedef struct{
	u8				language;
	u16				bgcolor;
	u16				fgcolor;
	GUI_FONT	font;
	FIL				f16;
	FIL				f32;
}_briupFont_base;

//初始化GUI
void	briupFontInit(void);
//绘制字体
void	briupFontDrawText(u16 left, u16 top, u8* text, u16 color, u16 bg_color, GUI_FONT font);
//获取背景色
u16		briupFontGetBGColor(void);
//绘制中文
u8	briupFontDrawGbkFont(u16 left, u16 top, u8* gbk, u16 color, GUI_FONT font);



#endif
