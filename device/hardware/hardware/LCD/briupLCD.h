
#ifndef __BALLANCE_LCD_H__
#define __BALLANCE_LCD_H__
#include "sys.h"
#include "briupFsmc.h"
#include "jpstm32_sysclk.h"
#include "ff.h"
//��Ļ�����ṹ�嶨��
typedef struct
{
	u16 width;	//��Ļ��� 480
	u16 height; //��Ļ�߶� 320
	u16 id;		//��Ļ��ʶ��
	u8 dir;		//
	u8 wramcmd; //дRAM����
	u8 setxcmd; //���ú���������
	u8 setycmd; //��������������
}_lcd_dev;

extern _lcd_dev lcddev;
extern u16 POINT_COLOR;
extern u16 BACK_COLOR;

//�ᡢ�����л�
#define	LCD_HOR_MODE	0
#define	LCD_VER_MODE	1
#define	LCD_VIEW_MODE	LCD_VER_MODE//LCD_HOR_MODE
//�������
#define	BLIGHT			PBxOut(0)
#define	BLIGHT_ON		1
#define	BLIGHT_OFF	0

//0Ϊ���� 1Ϊ����
#define	USE_HORIZONTAL	1

#define LCD_LED_ON()	GPIOB->ODR |= 0x01;
#define LCD_LED_OFF()	GPIOB->ODR &= ~0x01;
#define LCD_WIDTH_MAX	320
#define LCD_HIGH_MAX	480

//LCD��ַ�ṹ��
typedef struct
{
	u16 LCD_REG;	//Register
	u16 LCD_RAM;	//������ʴ洢��
} LCD_TypeDef;
//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A10��Ϊ�������������� 
//ע������ʱSTM32�ڲ�������һλ����! 111110=0X3E			    
#define LCD_BASE        ((u32)(0x6C000000 | 0x000007FE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)

#define	LCD_RST_SET  GPIOC->BSRR=1<<5    //��λ			PC5
#define	LCD_RST_CLR  GPIOC->BRR=1<<5    //��λ			PC5


//ɨ�跽����
#define L2R_U2D  0 //������,���ϵ���
#define L2R_D2U  1 //������,���µ���
#define R2L_U2D  2 //���ҵ���,���ϵ���
#define R2L_D2U  3 //���ҵ���,���µ���

#define U2D_L2R  4 //���ϵ���,������
#define U2D_R2L  5 //���ϵ���,���ҵ���
#define D2U_L2R  6 //���µ���,������
#define D2U_R2L  7 //���µ���,���ҵ���	 

#define DFT_SCAN_DIR  L2R_U2D  //Ĭ�ϵ�ɨ�跽��
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define RED       	0x001F //0xF800(����) 
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define BLUE         0xF800//0x001F(����)
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

//ͼƬ���Խṹ��
typedef struct{
	//ͼƬ��Ⱥ͸߶�
	u16	imgW;
	u16 imgH;
	//������x  ������y
	u16 localX;
	u16 localY;
	//�����ٶ�	�����ٶ�
	short Vx;	//X���ƶ��ٶ�
	short Vy;	//Y���ƶ��ٶ�
	//ͼƬ��ʾģʽ
	//drawMode = 0 :	����ͼƬ���õ�ɫBAKC_COLOR���
	//drawMode = 1 :	����ͼƬ
	//drawMode = 2 :	���ֲ���ͼƬ(�ֲ�ˢ��)
	u8 drawMode;
	//ͼƬ��Դ(����ת��������)
	unsigned char * imgArr;
}ImgTypeDef;

/* * * * * * * * * * * * * * * * * * * * * * * * *
 * ���ʶ���
 * * * * * * * * * * * * * * * * * * * * * * * * */
//�ַ����С
typedef enum
{
	P_S16 = 16,
	P_S32 = 32,
}PenSize;
//�ַ���д����
typedef enum
{
	P_DIR_HOR,
	P_DIR_VER
}PenDirect;
typedef enum
{
	P_SET_NOBRUSH, P_SET_BRUSH
}PenBrush;
//����
typedef struct{
	u16				color;
	u16				bg_color;
	PenSize		p_size;
	PenBrush	brush;
	PenDirect	direct;
}LcdPen;


void briupLcdInit(void);	//Һ������ʼ������
void briupLcdDisplayOn(void);	//����ʾģʽ								//����ʾ
void briupLcdDisplayOff(void);  //����ʾ
void briupLcdClear(u16 Color);	 												//����

//���ٻ�����
void briupLcdFastDrawDirection(u16 x1, u16 x2, u16 y1,u16 y2,u16 color, u8 full);
//���ٻ���
void briupLcdFastDrawPoint(u16 x, u16 y, u16 color);
//���ٻ���
void briupLcdFastDrawLine(u16 x1, u16 y1,u16 x2, u16 y2, u16 color);
//���ٻ�Բ
void briupLcdFastDrawCircle( u16 x, u16 y, u16 r, u16 color, u8 full);

//��LCD��д������
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
//��ȡLCDָ���Ĵ���������
u16 LCD_ReadReg(u8 LCD_Reg);

//��ʾ�ַ���
void briupLcdShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode,u16 point_colar,u16 back_colar);
//��ʾ����
void briupLcdShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);


//���ù��λ��
void lcdSetCursor(u16 x, u16 y);
//�趨һ��������ʾ��
void lcdSetWindow(u16 x_start, u16 y_start, u16 x_end, u16 y_end);

//===================================
//		LCD��ʾͼƬ��ؽӿ�
//ͼƬ���Խṹ���ʼ�������ӿ�
void briupLcdImageInit( ImgTypeDef * img, u16 imgW, u16 imgH,\
						u16 localX, u16 localY, \
						unsigned char * imgArr);
//ͼƬ��ʾ����
void briupLcdImageDraw( ImgTypeDef * img);

//����Ļ�ϻ���һ�����ص�
void lcdDrawPoint(u16 x, u16 y, LcdPen* pen);
//����һ����4��������ɵĵ�
void lcdDrawBigPoint(u16 x, u16 y, LcdPen* pen);
//����Ļ�ϻ���һ��ֱ��
void lcdDrawLine(u16 x1, u16 y1, u16 x2, u16 y2, LcdPen* p);
//����Ļ�ϻ���һ������
void lcdDrawRect(u16 x, u16 y, u16 width, u16 height, LcdPen*p);
//����һ���ַ�,�ɹ�����0,���򷵻ط���
u8 lcdDrawChr(u16 x, u16 y, u8 ch, LcdPen* p);
//��ָ��λ�û���һ���ַ���
u8 lcdDrawStr(u16 x, u16 y, u8* str, LcdPen* p);
//֧��GUI�ӿڵĺ���
void	lcdGuiDrawPoint(u16 x, u16 y, u16 color);
void	lcdGuiFill(u16 x, u16 y, u16 w, u16 h, u16 color);
u8 Bgp_Show(TCHAR* path);
#endif
