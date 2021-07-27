
#ifndef __BALLANCE_LCD_H__
#define __BALLANCE_LCD_H__
#include "sys.h"
#include "briupFsmc.h"
#include "jpstm32_sysclk.h"
#include "ff.h"
//屏幕参数结构体定义
typedef struct
{
	u16 width;	//屏幕宽度 480
	u16 height; //屏幕高度 320
	u16 id;		//屏幕标识符
	u8 dir;		//
	u8 wramcmd; //写RAM命令
	u8 setxcmd; //设置横坐标命令
	u8 setycmd; //设置纵坐标命令
}_lcd_dev;

extern _lcd_dev lcddev;
extern u16 POINT_COLOR;
extern u16 BACK_COLOR;

//横、竖屏切换
#define	LCD_HOR_MODE	0
#define	LCD_VER_MODE	1
#define	LCD_VIEW_MODE	LCD_VER_MODE//LCD_HOR_MODE
//背光控制
#define	BLIGHT			PBxOut(0)
#define	BLIGHT_ON		1
#define	BLIGHT_OFF	0

//0为竖屏 1为横屏
#define	USE_HORIZONTAL	1

#define LCD_LED_ON()	GPIOB->ODR |= 0x01;
#define LCD_LED_OFF()	GPIOB->ODR &= ~0x01;
#define LCD_WIDTH_MAX	320
#define LCD_HIGH_MAX	480

//LCD地址结构体
typedef struct
{
	u16 LCD_REG;	//Register
	u16 LCD_RAM;	//随机访问存储器
} LCD_TypeDef;
//使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=11 A10作为数据命令区分线 
//注意设置时STM32内部会右移一位对其! 111110=0X3E			    
#define LCD_BASE        ((u32)(0x6C000000 | 0x000007FE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)

#define	LCD_RST_SET  GPIOC->BSRR=1<<5    //复位			PC5
#define	LCD_RST_CLR  GPIOC->BRR=1<<5    //复位			PC5


//扫描方向定义
#define L2R_U2D  0 //从左到右,从上到下
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上

#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左	 

#define DFT_SCAN_DIR  L2R_U2D  //默认的扫描方向
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define RED       	0x001F //0xF800(竖屏) 
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define BLUE         0xF800//0x001F(竖屏)
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0X457 
#define BRRED 			0XFC07 
#define GRAY_A  			0X8430 
#define GRAY_B			0xC638
//GUI

#define DARKBLUE      	 0X01CF	
#define LIGHTBLUE      	 0X7D7C	
#define GRAYBLUE       	 0X5458 

#define LIGHTGREEN     	0X841F 
//#define LIGHTGRAY     0XEF5B 
#define LGRAY 			 		0XC618 

#define LGRAYBLUE      	0XA651 
#define LBBLUE          0X2B12 

//图片属性结构体
typedef struct{
	//图片宽度和高度
	u16	imgW;
	u16 imgH;
	//横坐标x  纵坐标y
	u16 localX;
	u16 localY;
	//横向速度	纵向速度
	short Vx;	//X轴移动速度
	short Vy;	//Y轴移动速度
	//图片显示模式
	//drawMode = 0 :	擦除图片，用底色BAKC_COLOR填充
	//drawMode = 1 :	绘制图片
	//drawMode = 2 :	部分擦除图片(局部刷新)
	u8 drawMode;
	//图片来源(经过转换的数组)
	unsigned char * imgArr;
}ImgTypeDef;

/* * * * * * * * * * * * * * * * * * * * * * * * *
 * 画笔定义
 * * * * * * * * * * * * * * * * * * * * * * * * */
//字符点大小
typedef enum
{
	P_S16 = 16,
	P_S32 = 32,
}PenSize;
//字符书写方向
typedef enum
{
	P_DIR_HOR,
	P_DIR_VER
}PenDirect;
typedef enum
{
	P_SET_NOBRUSH, P_SET_BRUSH
}PenBrush;
//画笔
typedef struct{
	u16				color;
	u16				bg_color;
	PenSize		p_size;
	PenBrush	brush;
	PenDirect	direct;
}LcdPen;


void briupLcdInit(void);	//液晶屏初始化函数
void briupLcdDisplayOn(void);	//打开显示模式								//开显示
void briupLcdDisplayOff(void);  //关显示
void briupLcdClear(u16 Color);	 												//清屏

//快速画矩形
void briupLcdFastDrawDirection(u16 x1, u16 x2, u16 y1,u16 y2,u16 color, u8 full);
//快速画点
void briupLcdFastDrawPoint(u16 x, u16 y, u16 color);
//快速画线
void briupLcdFastDrawLine(u16 x1, u16 y1,u16 x2, u16 y2, u16 color);
//快速画圆
void briupLcdFastDrawCircle( u16 x, u16 y, u16 r, u16 color, u8 full);

//向LCD中写入数据
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
//读取LCD指定寄存器的数据
u16 LCD_ReadReg(u8 LCD_Reg);

//显示字符串
void briupLcdShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode,u16 point_colar,u16 back_colar);
//显示数字
void briupLcdShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);


//设置光标位置
void lcdSetCursor(u16 x, u16 y);
//设定一个矩形显示区
void lcdSetWindow(u16 x_start, u16 y_start, u16 x_end, u16 y_end);

//===================================
//		LCD显示图片相关接口
//图片属性结构体初始化函数接口
void briupLcdImageInit( ImgTypeDef * img, u16 imgW, u16 imgH,\
						u16 localX, u16 localY, \
						unsigned char * imgArr);
//图片显示设置
void briupLcdImageDraw( ImgTypeDef * img);

//在屏幕上绘制一个像素点
void lcdDrawPoint(u16 x, u16 y, LcdPen* pen);
//绘制一个由4个像素组成的点
void lcdDrawBigPoint(u16 x, u16 y, LcdPen* pen);
//在屏幕上绘制一条直线
void lcdDrawLine(u16 x1, u16 y1, u16 x2, u16 y2, LcdPen* p);
//在屏幕上绘制一个矩形
void lcdDrawRect(u16 x, u16 y, u16 width, u16 height, LcdPen*p);
//绘制一个字符,成功返回0,否则返回非零
u8 lcdDrawChr(u16 x, u16 y, u8 ch, LcdPen* p);
//在指定位置绘制一个字符串
u8 lcdDrawStr(u16 x, u16 y, u8* str, LcdPen* p);
//支持GUI接口的函数
void	lcdGuiDrawPoint(u16 x, u16 y, u16 color);
void	lcdGuiFill(u16 x, u16 y, u16 w, u16 h, u16 color);
u8 Bgp_Show(TCHAR* path);
#endif
