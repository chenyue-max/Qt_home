#include "briupLCD.h"
#include "briupLCDFont.h"
#include "Debug_usart.h"
#include "ff.h"
#include "malloc.h"

//LCD�Ļ�����ɫ�ͱ���ɫ	   
u16 POINT_COLOR=0x0000;	//������ɫ
u16 BACK_COLOR=0xFFFF;  //����ɫ 

//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;
	
		   
//д�Ĵ�������
//regval:�Ĵ���ֵ
void LCD_WR_REG(u16 regval)
{ 
	LCD->LCD_REG=regval;//д��Ҫд�ļĴ������	 
}
//дLCD����
//data:Ҫд���ֵ
void LCD_WR_DATA(u16 data)
{										    	   
	LCD->LCD_RAM=data;		 
}
//��LCD����
//����ֵ:������ֵ
u16 LCD_RD_DATA(void)
{										    	   
	return LCD->LCD_RAM;		 
}					   
//д�Ĵ���
//LCD_Reg:�Ĵ�����ַ
//LCD_RegValue:Ҫд�������
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{	
	LCD->LCD_REG = LCD_Reg;		//д��Ҫд�ļĴ������	 
	LCD->LCD_RAM = LCD_RegValue;//д������	    		 
}	   
//���Ĵ���
//LCD_Reg:�Ĵ�����ַ
//����ֵ:����������
u16 LCD_ReadReg(u8 LCD_Reg)
{										   
	LCD_WR_REG(LCD_Reg);		//д��Ҫ���ļĴ������
	delayMs(3);
	return LCD_RD_DATA();		//���ض�����ֵ
}   


void  briupLcdInit(void)
{
	briupFSMCInit();
	lcddev.id = 0;
	
	LCD_WR_REG( 0x00b0);
	LCD_WR_DATA( 0x00);
	
	LCD_WR_REG( 0x00d3);
	LCD_RD_DATA();
	LCD_RD_DATA();
	lcddev.id=LCD_RD_DATA();
	lcddev.id<<=8;
	lcddev.id|=LCD_RD_DATA();
	//put_c("%x\r\n", lcddev.id);
	
	LCD_WR_REG(0xC0);  		//��Դ����
	LCD_WR_DATA(0x0a);     //1e  contrast
	LCD_WR_DATA(0x0a);     //1e  contrast
	
		LCD_WR_REG(0xC1);				//	��Դ����
	LCD_WR_DATA(0x44);    //41
	
		LCD_WR_REG(0XC5);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x09);  //vcom  10
	
		LCD_WR_REG(0xB1);				//֡���ʿ���
	LCD_WR_DATA(0x90);			//56HZ
	LCD_WR_DATA(0x11);			//25 clocks
	
		LCD_WR_REG(0xB4);			//	��ʾ��ת����
	LCD_WR_DATA(0x02);
	
		LCD_WR_REG(0xB7);			//����ģʽ���ã�������������
	LCD_WR_DATA(0xC6);
	
		LCD_WR_REG(0xB6);		//	��ʾ���ܿ���
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x22);//0 GS SS SM ISC[3:0];??GS SS??????,????R36
	LCD_WR_DATA(0x3B);

	LCD_WR_REG(0xE0);			//ͼ��Ҷȿ���
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x04);
	LCD_WR_DATA(0x06);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x3F);
	LCD_WR_DATA(0xAC);
	LCD_WR_DATA(0x4F);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x21);
	LCD_WR_DATA(0x24);
	LCD_WR_DATA(0x0F);
	
	LCD_WR_REG(0XE1);			//����٤�����
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x1B);
	LCD_WR_DATA(0x1E);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x06);
	LCD_WR_DATA(0x30);
	LCD_WR_DATA(0xff);
	LCD_WR_DATA(0x40);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x0D);
	LCD_WR_DATA(0x39);
	LCD_WR_DATA(0x3B);
	LCD_WR_DATA(0x0F);
	
	LCD_WR_REG(0XF2);
	LCD_WR_DATA(0x18);
	LCD_WR_DATA(0xA3);
	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0xB2);
	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0xFF);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x00);
	
	LCD_WR_REG(0XF7);
	LCD_WR_DATA(0xA9);
	LCD_WR_DATA(0x91);
	LCD_WR_DATA(0x2D);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x4F);
	
	LCD_WR_REG(0XFB);
	LCD_WR_DATA(0x21);
	LCD_WR_DATA(0x04);
	
	LCD_WR_REG(0x36);				//����ɨ�跽ʽ
	LCD_WR_DATA(0x00);		 //88 48   68   ??????
	
	LCD_WR_REG(0x3A);			//	�ӿ����ظ�ʽ��ѡ��16λ�Ľӿ�ģʽ
	LCD_WR_DATA(0x55);
	
	LCD_WR_REG(0xF9);  
	LCD_WR_DATA(0x00);  
	LCD_WR_DATA(0x08);
	
	LCD_WR_REG(0xF4);  
	LCD_WR_DATA(0x00);  
	LCD_WR_DATA(0x00); 
	LCD_WR_DATA(0x08);  
	LCD_WR_DATA(0x91); 
	LCD_WR_DATA(0x04);
	LCD_WR_REG(0x11);
	
	delayMs(120);
	LCD_WR_REG(0x29);
	
	lcddev.setxcmd=0x2A;
	lcddev.setycmd=0x2B;
	lcddev.wramcmd=0x2C;
#if USE_HORIZONTAL==1	//ʹ�ú���	  
	lcddev.dir=1;//����
	lcddev.width=480;
	lcddev.height=320;
	LCD_WriteReg(0x36,0x60);
#else//����
	lcddev.dir=0;//����				 	 		
	lcddev.width=320;
	lcddev.height=480;	
	LCD_WriteReg(0x36,0x08);
#endif
	
	LCD_LED_ON();
	briupLcdClear(WHITE);
}

//LCD_DisplayOn
void briupLcdDisplayOn(void)
{
	 LCD_WriteReg(0x0029,0);
}
//LCD_Displayoff
void briupLcdDisplayOff(void)
{
	LCD_WriteReg(0x0028,0);
}

void briupLcdClear(u16 Color)
{
	BACK_COLOR = Color;
	briupLcdFastDrawDirection( 0, lcddev.width-1, 0,lcddev.height-1, Color, 1);
}

//���ù��λ��
void lcdSetCursor(u16 x, u16 y)
{
	LCD->LCD_REG = 0x2a;	//���
	LCD->LCD_RAM = x >> 8;
	LCD->LCD_RAM = x;
	LCD->LCD_RAM = x >> 8;
	LCD->LCD_RAM = x;
	LCD->LCD_REG = 0x2b;
	LCD->LCD_RAM = y >> 8;
	LCD->LCD_RAM = y;
	LCD->LCD_RAM = y >> 8;
	LCD->LCD_RAM = y;
	//��ʼд�Ĵ���
	LCD->LCD_REG= 0x2c;
}
//�趨һ��������ʾ��
void lcdSetWindow(u16 x_start, u16 y_start, u16 x_end, u16 y_end)
{
	LCD->LCD_REG = 0x2a;
	LCD->LCD_RAM = x_start >> 8;
	LCD->LCD_RAM = x_start;
	LCD->LCD_RAM = x_end >> 8;
	LCD->LCD_RAM = x_end;
	LCD->LCD_REG = 0x2b;
	LCD->LCD_RAM = y_start >> 8;
	LCD->LCD_RAM = y_start;
	LCD->LCD_RAM = y_end >> 8;
	LCD->LCD_RAM = y_end;
	
	LCD->LCD_REG= 0x2c;
}

//���ٻ���
void briupLcdFastDrawPoint(u16 x, u16 y, u16 color)
{
	LCD->LCD_REG = 0x2a;	//���
	LCD->LCD_RAM = x >> 8;
	LCD->LCD_RAM = x;
	LCD->LCD_RAM = x >> 8;
	LCD->LCD_RAM = x;
	LCD->LCD_REG = 0x2b;
	LCD->LCD_RAM = y >> 8;
	LCD->LCD_RAM = y;
	LCD->LCD_RAM = y >> 8;
	LCD->LCD_RAM = y;
	
	LCD->LCD_REG= 0x2c;
	LCD->LCD_RAM=color;
}

//���ٻ���
void briupLcdFastDrawLine(u16 x1, u16 y1,u16 x2, u16 y2, u16 color)
{
	int dx = x2-x1;
	int dy = y2-y1;
	int y = y1;
	int eps = 0, i;
	
	LCD->LCD_REG = 0x2a;	//���
	LCD->LCD_RAM = x1 >> 8;
	LCD->LCD_RAM = x1;
	LCD->LCD_RAM = x2 >> 8;
	LCD->LCD_RAM = x2;
	LCD->LCD_REG = 0x2b;
	LCD->LCD_RAM = y1 >> 8;
	LCD->LCD_RAM = y1;
	LCD->LCD_RAM = y2 >> 8;
	LCD->LCD_RAM = y2;
	
	LCD->LCD_REG= 0x2c;
	if(dx == 0)
		for( i = y1; i <= y2; i++)
			LCD->LCD_RAM = color;
	else if( dy == 0)
		for( i = x1; i <= x2; i++)
			LCD->LCD_RAM = color;
	else
		for( i = x1; i <= x2; i++)
		{
			LCD->LCD_RAM = color;
			eps+= dy;
			if( (eps << 1) >= dx)
			{
				y++;
				eps -= dx;
			}
		}
}


//���ٻ�����
void briupLcdFastDrawDirection(u16 x1, u16 x2, u16 y1,u16 y2,u16 color, u8 full)
{
	u16 i,j;
	
	if( full == 1)
	{
		LCD->LCD_REG = 0x2a;
		LCD->LCD_RAM = x1 >> 8;
		LCD->LCD_RAM = x1;
		LCD->LCD_RAM = x2 >> 8;
		LCD->LCD_RAM = x2;
		LCD->LCD_REG = 0x2b;
		LCD->LCD_RAM = y1 >> 8;
		LCD->LCD_RAM = y1;
		LCD->LCD_RAM = y2 >> 8;
		LCD->LCD_RAM = y2;
		
		LCD->LCD_REG= 0x2c;
		for(i = x1;i <= x2;i++)
			for(j = y1; j <= y2; j++)
				LCD->LCD_RAM=color;
	}else
	{
		//�Ȼ�����
		LCD->LCD_REG = 0x2a;
		LCD->LCD_RAM = x1 >> 8;
		LCD->LCD_RAM = x1;
		LCD->LCD_RAM = x2 >> 8;
		LCD->LCD_RAM = x2;
		LCD->LCD_REG = 0x2b;
		LCD->LCD_RAM = y1 >> 8;
		LCD->LCD_RAM = y1;
		LCD->LCD_RAM = y1 >> 8;
		LCD->LCD_RAM = y1;
		
		LCD->LCD_REG= 0x2c;
		for(i = x1; i <= x2; i++)
			LCD->LCD_RAM=color;
		
		LCD->LCD_REG = 0x2b;
		LCD->LCD_RAM = y2 >> 8;
		LCD->LCD_RAM = y2;
		LCD->LCD_RAM = y2 >> 8;
		LCD->LCD_RAM = y2;
		
		LCD->LCD_REG= 0x2c;
		for(i = x1; i <= x2; i++)
			LCD->LCD_RAM=color;
		
		//�ٻ�����
		LCD->LCD_REG = 0x2b;
		LCD->LCD_RAM = y1 >> 8;
		LCD->LCD_RAM = y1;
		LCD->LCD_RAM = y2 >> 8;
		LCD->LCD_RAM = y2;
		LCD->LCD_REG = 0x2a;
		LCD->LCD_RAM = x1 >> 8;
		LCD->LCD_RAM = x1;
		LCD->LCD_RAM = x1 >> 8;
		LCD->LCD_RAM = x1;
		
		LCD->LCD_REG= 0x2c;
		for(i = y1; i <= y2; i++)
			LCD->LCD_RAM=color;
		
		LCD->LCD_REG = 0x2a;
		LCD->LCD_RAM = x2 >> 8;
		LCD->LCD_RAM = x2;
		LCD->LCD_RAM = x2 >> 8;
		LCD->LCD_RAM = x2;
		
		LCD->LCD_REG= 0x2c;
		for(i = y1; i <= y2; i++)
			LCD->LCD_RAM=color;
	}
}

void briupLcdFastDrawCircle( u16 xc, u16 yc, u16 r, u16 color, u8 full)
{
	int x = 0, y = r, yi, d;

	d = 3 - 2 * r;

	if (full) 
	{
		// �����䣨��ʵ��Բ��
		while (x <= y) {
			for (yi = x; yi <= y; yi++)
			{
				briupLcdFastDrawPoint(xc + x, yc + y, color);
				briupLcdFastDrawPoint(xc - x, yc + y, color);
				briupLcdFastDrawPoint(xc + x, yc - y, color);
				briupLcdFastDrawPoint(xc - x, yc - y, color);
				briupLcdFastDrawPoint(xc + y, yc + x, color);
				briupLcdFastDrawPoint(xc - y, yc + x, color);
				briupLcdFastDrawPoint(xc + y, yc - x, color);
				briupLcdFastDrawPoint(xc - y, yc - x, color);
			}

			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	} else 
	{
		// �������䣨������Բ��
		while (x <= y) {
			briupLcdFastDrawPoint(xc + x, yc + y, color);
			briupLcdFastDrawPoint(xc - x, yc + y, color);
			briupLcdFastDrawPoint(xc + x, yc - y, color);
			briupLcdFastDrawPoint(xc - x, yc - y, color);
			briupLcdFastDrawPoint(xc + y, yc + x, color);
			briupLcdFastDrawPoint(xc - y, yc + x, color);
			briupLcdFastDrawPoint(xc + y, yc - x, color);
			briupLcdFastDrawPoint(xc - y, yc - x, color);
			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	}
}



//����Ļ�ϻ���һ�����ص�
void lcdDrawPoint(u16 x, u16 y, LcdPen* pen)
{
	lcdSetCursor(x, y);
	LCD->LCD_REG = 0x2c;
	LCD->LCD_RAM = pen->color;
}

//����һ�����ĸ�������ɵĵ�
void lcdDrawBigPoint(u16 x, u16 y, LcdPen* p)
{
	lcdDrawPoint(x, y,  p);
	lcdDrawPoint(x+1, y, p);
	lcdDrawPoint(x, y+1, p);
	lcdDrawPoint(x+1, y+1, p);
}


//����һ��ֱ��
void lcdDrawLine(u16 x1, u16 y1, u16 x2, u16 y2, LcdPen* p)
{
	float temp;
	u16 x_temp;
	u16 y_temp;
	
	if(x2==x1)
	{
		for(y_temp=y1; y_temp<=y2; y_temp++)
		{
			lcdDrawPoint(x1, y_temp, p);
		}
	}
	else
	{
		temp = (((float)(y2-y1))/((float)(x2-x1)));
		for(x_temp=x1; x_temp<=x2; x_temp++)
		{
			y_temp = temp*(x_temp-x1)+y1;
			lcdDrawPoint(x_temp, y_temp, p);
		}
	}
}

//����һ������
void lcdDrawRect(u16 x, u16 y, u16 width, u16 height, LcdPen*p)
{
	u32 i;
	u32 total = width*height;
	if(P_SET_BRUSH == p->brush)
	{
		lcdSetWindow(x, y, x+width-1, y+height-1);
		for(i=0; i<total; i++){
			LCD->LCD_RAM = p->color;
		}
	}
	else
	{
		lcdDrawLine(x, y, x+width, y, p);
		lcdDrawLine(x, y+height, x+width, y+height, p);
		lcdDrawLine(x, y, x, y+height, p);
		lcdDrawLine(x+width, y, x+width, y+height, p);
	}
}

//����һ���ַ�
u8 lcdDrawChr(u16 x, u16 y, u8 ch, LcdPen* p)
{
	u8	byte_x;//��ǰ����������ֽ���
	u8	byte, bit;
	u8	temp;
	u16 y0 = y;//��ǰ������ռ���ظ߶�
	
	ch -= ' ';//�ֿ��дӡ� ����ʼ��ʾ
	
	switch(p->p_size)
	{
		case P_S16:
			byte_x = 16;
			break;
		case P_S32:
			byte_x = 64;
			break;
		default:
			return 1;
	}
	
	//���ѭ����ʾ����ӡÿ���ַ�
	for(byte=0; byte<byte_x; byte++)
	{
		//��ȡ�ַ���Ӧ�ĵ����ֽ�
		switch(p->p_size)
		{
			case P_S16:
				temp = asc2_1608[ch][byte];
				break;
			case P_S32:
				temp = asc2_3210[ch][byte];
				break;
			default:
				return 1;
		}
		
		//��λ��ʾ��Һ����
		for(bit=0; bit<8; bit++)
		{
			if(temp&0x80)
			{
				lcdDrawPoint(x, y, p);
			}
			temp <<= 1;//��ӡ��һλ
			y++;//��ֱ��������һ������
			if(y>lcddev.height)
			{
				return 1;
			}
		}

		if((y-y0)==p->p_size)
		{
			y = y0;
			x++;
			//�ж��Ƿ񳬳�ˮƽ�߽�
			if(x>lcddev.width)
			{
				return 1;
			}
		}
	}
	return 0;
}
//��ָ��λ�û���һ���ַ������ɹ�����0���򷵻ط�0
u8 lcdDrawStr(u16 x, u16 y, u8* str, LcdPen* p)
{
	u8 inc = 0;
	
	switch(p->p_size)
	{
		case P_S16:
			inc = 16;
			break;
		case P_S32:
			inc = 32;
			break;
		default:
			return 1;
	}
	
	while(*str)
	{
		if(P_DIR_HOR==p->direct)
		{
			if(lcdDrawChr(x, y, *str, p))
			{
				return 1;
			}
			x += inc/2;	
			str += 1;
		}
		else if(P_DIR_VER==p->direct)
		{
			
			if(lcdDrawChr(x, y, *str, p))
			{
				return 1;
			}	
			str += 1;
			y += inc;
		}
	}
	return 0;
}

//֧��GUI�����Ľӿ�
void	lcdGuiDrawPoint(u16 x, u16 y, u16 color)
{
	lcdSetCursor(x, y);
	LCD->LCD_REG = 0x2c;
	LCD->LCD_RAM = color;
}
void	lcdGuiFill(u16 x, u16 y, u16 w, u16 h, u16 color)
{
	u32 i = 0;
	u32 total = w*h;
	lcdSetWindow(x, y, x+w-1, y+h-1);
	for(i=0; i<total; i++){
			LCD->LCD_RAM = color;
	}
}



//=======================================================================================
//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}

//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void briupLcdShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode,u16 point_colar,u16 back_colar)
{
	u8 temp=0,t1,t,size_x=0;
#pragma diag_suppress 550
	u16 Supplementary_data_x = 0;
	u16 y0=y;
	u16 colortemp=POINT_COLOR;
	//���ô���		   
	num=num-' ';//�õ�ƫ�ƺ��ֵ
	if(!mode) //�ǵ��ӷ�ʽ
	{
				if(size == 12)size_x = 12;  //����1206����
				if(size == 16)size_x = 16;	//����1608���� 	                          
				if(size == 32){size_x = 64;Supplementary_data_x=960;}	//����3210���� 
		for(t=0;t<size_x;t++)
	    {   
				if(size == 12)temp=asc2_1206[num][t];  //����1206����
				if(size == 16)temp=asc2_1608[num][t];	 //����1608���� 	                          
				if(size == 32)temp=asc2_3210[num][t];	 //����3210����
				for(t1=0;t1<8;t1++)
				{			    
					if(temp&0x80)POINT_COLOR=colortemp;
					else POINT_COLOR=BACK_COLOR;
					briupLcdFastDrawPoint( x, y, POINT_COLOR);	
					temp<<=1;
					y++;
					//if(x>=lcddev.width+Supplementary_data_x){POINT_COLOR=colortemp;return;}//��������
					if((y-y0)==size)
					{
						y=y0;
						x++;
						//if(x>=lcddev.width+Supplementary_data_x){POINT_COLOR=colortemp;return;}//��������
						break;
					}
				}  	 
	    }    
	}else//���ӷ�ʽ
	{
			if(size == 12)size_x = 12;  //����1206����
			if(size == 16)size_x = 16;	//����1608���� 	                          
			if(size == 32){size_x = 64;Supplementary_data_x=960;}	//����3210���� 
	    for(t=0;t<size_x;t++)
	    {   
				if(size == 12)temp=asc2_1206[num][t];  //����1206����
				if(size == 16)temp=asc2_1608[num][t];	 //����1608���� 	                          
				if(size == 32)temp=asc2_3210[num][t];	 //����3210����                          
				for(t1=0;t1<8;t1++)
				{
					if(temp&0x80)briupLcdFastDrawPoint( x, y, point_colar);
					else briupLcdFastDrawPoint( x, y, back_colar);
					temp<<=1;
					y++;
					//if(x>=lcddev.height+Supplementary_data_x){POINT_COLOR=colortemp;return;}//��������
					if((y-y0)==size)
					{
						y=y0;
						x++;
						//if(x>=lcddev.width+Supplementary_data_x){POINT_COLOR=colortemp;return;}//��������
						break;
					}
				}  	 
	    }     
	}
	POINT_COLOR=colortemp;	    	   	 	  
}   

//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);
//len:����(��Ҫ��ʾ��λ��)
//size:�����С 12 / 16
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void briupLcdShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)briupLcdShowChar(x+(size/2)*t,y,'0',size,mode&0X01,POINT_COLOR,0xffff);  
				else briupLcdShowChar(x+(size/2)*t,y,' ',size,mode&0X01,POINT_COLOR,0xffff);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	briupLcdShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01,POINT_COLOR,0xffff); 
	}
}


//============================================================================================
//		LCD��ʾͼƬ��ؽӿ�
//ͼƬ���Խṹ���ʼ�������ӿ�
void briupLcdImageInit( ImgTypeDef * img, u16 imgW, u16 imgH,\
						u16 localX, u16 localY, \
						unsigned char * imgArr)
{
	img->imgH = imgH;
	img->imgW = imgW;
	img->localX = localX;
	img->localY = localY;
	
	img->Vx = 0;	//Ĭ��ͼƬ�ƶ��ٶ�
	img->Vy = 0;
	img->drawMode = 1;	//Ĭ����ʾģʽ
	
	img->imgArr = imgArr;
}

//ͼƬ��ʾ����
void briupLcdImageDraw( ImgTypeDef * img)
{
	u16 imgColor;
	u16 i,j;
	u16 x1, y1, x2, y2;
	u16 offset = 3;
	//�ֲ�ˢ�´���
	if( img->drawMode == 2)
	{
		if( img->Vx > 0)
		{
			x1 = img->localX - img->Vx - 1;
			x2 = img->localX;
			y1 = img->localY - offset;
			y2 = img->localY + img->imgH + offset;
			briupLcdFastDrawDirection( x1,x2,y1,y2,BACK_COLOR,1);
		}
		else if( img->Vx < 0)	//�����ƶ����ұ߻�����
		{
			x1 = img->localX + img->imgW;
			x2 = img->localX + img->imgW - img->Vx + 1;
			y1 = img->localY - offset;
			y2 = img->localY + img->imgH + offset;
			briupLcdFastDrawDirection( x1,x2,y1,y2,BACK_COLOR, 1);
		}
		
		if( img->Vy > 0)		//�����ƶ������滭����
		{
			x1 = img->localX - offset;
			x2 = img->localX + img->imgW + offset;
			y1 = img->localY - img->Vy - 1;
			y2 = img->localY;
			briupLcdFastDrawDirection( x1,x2,y1,y2,BACK_COLOR, 1);
		}
		else if( img->Vy < 0)	//�����ƶ������滭����
		{
			x1 = img->localX - offset;
			x2 = img->localX + img->imgW + offset;
			y1 = img->localY + img->imgH;
			y2 = img->localY + img->imgH - img->Vy + 1;
			briupLcdFastDrawDirection( x1,x2,y1,y2,BACK_COLOR,1 );
		}
		return;
	}
	
	//���ú�����ʾ����(�п�)
	LCD->LCD_REG = 0x2a;
	//������ʼ��SC[15:0]
	LCD->LCD_RAM = img->localX >> 8;	//��ʼ�и߰�λ
	LCD->LCD_RAM = img->localX & 0xff;	//��ʼ�еͰ�λ
	//���ý�����EC[15:0]
	LCD->LCD_RAM = (img->localX + img->imgW) >> 8;
	LCD->LCD_RAM = (img->localX + img->imgW) & 0xff;
	
	//����������ʾ����(�и�/ҳ��ַ)
	LCD->LCD_REG = 0x2b;
	LCD->LCD_RAM = img->localY >> 8;
	LCD->LCD_RAM = img->localY & 0xff;
	LCD->LCD_RAM = (img->localY+img->imgH)>>8;
	LCD->LCD_RAM = (img->localY+img->imgH)&0xff;
	
	//����ͼ������
	LCD->LCD_REG = 0x2c;
	
	//ȫ������
	if( img->drawMode == 0)
	{
		for( i = 0;i < img->imgH;i++)
			for( j = 0;j <= img->imgW;j++)
				LCD->LCD_RAM = BACK_COLOR;
	}
	//����ͼƬ
	if( img->drawMode == 1)
	{
		for( i = 0;i < img->imgH;i++)
		{
			for( j = 0;j <= img->imgW;j++)
			{
				imgColor = img->imgArr[(j + i*img->imgW)*2+1]<<8;
				imgColor |= img->imgArr[(j + i*img->imgW)*2];
				LCD->LCD_RAM = imgColor;
			}
		}
	}
}

/*************************************************
��SD����ȡͼƬ��ʾ��Һ������
ע�⣺��ǰΪ��������
			ͼƬ����Ϊȫ��ͼƬ
*************************************************/
FIL Bgp_File;
#define Bgp_Rnum	1276
ImgTypeDef Bgp_PICT;
#if 1
u8 Bgp_Show(TCHAR* path)
{
	UINT Bgp_Point;
	u16 circle;
	u16 i;
	u8 *Bgp = mymalloc(SRAMIN,Bgp_Rnum);
	if(Bgp == NULL)
		return 2;
	if(FR_OK != f_open(&Bgp_File,path,FA_READ))
	{
		return 1;
	}
	else
	{
		circle = Bgp_File.fsize / Bgp_Rnum;
		for(i=0;i<circle;i++)
		{
			if(FR_OK == f_read(&Bgp_File,Bgp,Bgp_Rnum,&Bgp_Point))
			{
				briupLcdImageInit(&Bgp_PICT,319,2,0,2*i,Bgp);
				briupLcdImageDraw(&Bgp_PICT);
			}
			else
				return 3;
		}
		f_close(&Bgp_File);
	}
	return 0;
}
#endif






