#include "briupTouch.h"
#include "jpstm32_sysclk.h"
#include "Debug_usart.h"
#define	LCD_WIDTH		480
#define	LCD_HEIGHT	320

static TouchTpyDef	t_pad = {
	tp_init,
	tp_scan,
	tp_adjust,
	0, 0, 0, 0,
	0,
	-0.130680, -0.085418, 508, 332,
	P_DIR_HOR,
	0x90, 0xd0
};

void tp_spiWbyte(u8 byte)
{
	u8 count=0;   
	for(count=0;count<8;count++)  
	{ 	  
		if(byte&0x80)
		{
			TP_IN_H();
		}
		else
		{
			TP_IN_L();
		}			   
		byte<<=1;
		TP_CLK_L(); 	 
		TP_CLK_H();		//��������Ч	        
	}		
}

u16 tp_readAD(u8 cmd)
{
	u8 count=0; 	  
	u16 Num=0; 
	TP_CLK_L();		//������ʱ�� 	 
	TP_IN_L(); 	//����������
	TP_CS_L(); 		//ѡ�д�����IC
	tp_spiWbyte(cmd);//����������
	delayUs(6);//ADS7846��ת��ʱ���Ϊ6us
	TP_CLK_L(); 	     	    
	delayUs(1);    	   
	TP_CLK_H();		//��1��ʱ�ӣ����BUSY	    	    
	TP_CLK_L(); 	     	    
	for(count=0;count<16;count++)//����16λ����,ֻ�и�12λ��Ч 
	{ 				  
		Num<<=1; 	 
		TP_CLK_L();	//�½�����Ч  	    	   
		TP_CLK_H();
		if(TP_OUT)Num++; 		 
	}  	
	Num>>=4;   	//ֻ�и�12λ��Ч.
	TP_CS_H();		//�ͷ�Ƭѡ	 
	return(Num);  
}

#define READ_TIMES 5 	//��ȡ����
#define LOST_VAL 1	  	//����ֵ
u16 tp_readXorY(u8 cmd)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum=0;
	u16 temp;

	for(i=0;i<READ_TIMES;i++)
	{
		buf[i]=tp_readAD(cmd);		 		    
	}
	for(i=0;i<READ_TIMES-1; i++)//����
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//��������
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)
	{
		sum+=buf[i];
	}

	temp=sum/(READ_TIMES-2*LOST_VAL);

	return temp;  
}

u8 tp_readXandY(u16* x, u16* y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=tp_readXorY(t_pad.cmdRdx);
	ytemp=tp_readXorY(t_pad.cmdRdy);	  												   
	*x=xtemp;
	*y=ytemp;
	return 0;//�����ɹ�
}

#define	ERR_RANGE	50	//��Χ
u8 tp_readXandY2(u16* x, u16* y)
{
	u16 x1,y1;
	u16 x2,y2;
	u8 flag;    
	flag=tp_readXandY(&x1,&y1);  	
	if(flag)
	{
		return(1);
	}
	flag=tp_readXandY(&x2,&y2);	   
	if(flag)
	{
		return(2);   
	}
	if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//ǰ�����β�����+-50��
			&&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
	{
		*x=(x1+x2)/2;
		*y=(y1+y2)/2;
		return 0;
	}
	else
	{
		return 3;
	}			
}

void tp_drawAdjustPoint(u16 x, u16 y, u16 color)
{
	LcdPen	pen;

	pen.color = color;
	pen.brush = P_SET_BRUSH;
	lcdDrawRect(x-1, y-1, 3, 3, &pen);
	lcdDrawLine(x-15, y, x+15, y, &pen);
	lcdDrawLine(x, y-15, x, y+15, &pen);
	pen.brush = P_SET_NOBRUSH;
	lcdDrawRect(x-5, y-5, 11, 11, &pen);
}

u8 tp_scan(u8 tp)
{
	if(TP_PEN==0)//�а�������
	{
		if(tp)
		{
			tp_readXandY2(&t_pad.currX, &t_pad.currY);//��ȡ��������
		}
		else if(tp_readXandY2(&t_pad.currX, &t_pad.currY))//��ȡ��Ļ����
		{
			//�����ת��Ϊ��Ļ����
			t_pad.currX = t_pad.xfac*t_pad.currX+t_pad.xoff;
			t_pad.currY = t_pad.yfac*t_pad.currY+t_pad.yoff;
		} 
		
		if((t_pad.penStat&TP_PRES_DOWN)==0)//֮ǰû�б�����
		{
			//�������� 
			t_pad.penStat = TP_PRES_DOWN|TP_CATH_PRES;
			//��¼��һ�ΰ���ʱ������ 
			t_pad.lastX = t_pad.currX;
			t_pad.lastY = t_pad.currY;

		}			   
	}
	else
	{
		if(t_pad.penStat&TP_PRES_DOWN)//֮ǰ�Ǳ����µ�
		{
			t_pad.penStat&=0x7F;//��ǰ����ɿ�	
		}
		else//֮ǰ��û�б�����
		{
			t_pad.lastX = 0;
			t_pad.lastY = 0;
			t_pad.currX = 0xFFFF;
			t_pad.currY = 0xFFFF;
		}	    
	}
	return t_pad.penStat&TP_PRES_DOWN;//���ص�ǰ�Ĵ���״̬
}


u8 tp_init(void)
{

	//��������֮ǰ,����ʹ��ʱ��.����ʵ���������������
	RCC->APB2ENR|=1<<3;    //PBʱ��ʹ��	   
	RCC->APB2ENR|=1<<7;    //PFʱ��ʹ��	   

	GPIOB->CRL&=0XFFFFF00F;//PB1  2
	GPIOB->CRL|=0X00000330; 
	GPIOB->ODR|=3<<1;      //PB1 2 ������� 	 
	GPIOF->CRH&=0XFFFFF000;
	GPIOF->CRH|=0X00000838;
	GPIOF->ODR|=7<<8;      //PF8,9,10 ȫ������	  
	tp_readXandY(&t_pad.currX, &t_pad.currY);//��һ�ζ�ȡ��ʼ��	

	briupLcdClear(WHITE);	
	if(t_pad.xfac>-0.000001&&t_pad.xfac<0.000001){
		if(tp_adjust()==0)
		{
			return 0;
		}
		else 
		{
			return 1;
		}
	}
	return 0;
}

u8 tp_adjust(void)
{
	u16 pos_temp[4][2];//���껺��ֵ
	u8  cnt=0;	
	u16 d1,d2;
	u32 tem1,tem2;
	float fac; 	
	u16 outtime=0;
				
	LcdPen	pen;
	pen.color = RED;
	pen.p_size = P_S16;
	
	cnt=0;
	
	briupLcdClear(WHITE);//����   

	tp_drawAdjustPoint(20, 20, RED);
	
	lcdDrawStr(100, 120, (u8*)"Click The Adjust Point To Adjust Touch Pad.", &pen);

	t_pad.penStat = 0;//���������ź� 
	t_pad.xfac = 0;//xfac��������Ƿ�У׼��,����У׼֮ǰ�������!�������	 

	while(1)//�������10����û�а���,���Զ��˳�
	{
		//ɨ����������
		t_pad.scan(1);
		if((t_pad.penStat&0xc0)==TP_CATH_PRES)//����������һ��(��ʱ�����ɿ���.)
		{	
			outtime=0;		
			t_pad.penStat&=~(1<<6);//��ǰ����Ѿ����������.

			pos_temp[cnt][0]=t_pad.currX;
			pos_temp[cnt][1]=t_pad.currY;
			cnt++;	  
			switch(cnt)
			{			   
				case 1:						 
					//�����1 
					tp_drawAdjustPoint(20,20,WHITE);
					//����2
					tp_drawAdjustPoint(LCD_WIDTH-20,20,RED);
					break;
				case 2:
					//�����2 
					tp_drawAdjustPoint(LCD_WIDTH-20,20,WHITE);
					//����3
					tp_drawAdjustPoint(20,LCD_HEIGHT-20,RED);
					break;
				case 3:
					//�����3 
					tp_drawAdjustPoint(20,LCD_HEIGHT-20,WHITE);
					//����4
					tp_drawAdjustPoint(LCD_WIDTH-20,LCD_HEIGHT-20,RED);
					break;
				case 4:	 //ȫ���ĸ����Ѿ��õ�
					//�Ա����
					tem1=abs(pos_temp[0][0]-pos_temp[1][0]);//x1-x2
					tem2=abs(pos_temp[0][1]-pos_temp[1][1]);//y1-y2
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);//�õ�1,2�ľ���

					tem1=abs(pos_temp[2][0]-pos_temp[3][0]);//x3-x4
					tem2=abs(pos_temp[2][1]-pos_temp[3][1]);//y3-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//�õ�3,4�ľ���
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05||d1==0||d2==0)//���ϸ�
					{
						cnt=0;
						tp_drawAdjustPoint(LCD_WIDTH-20,LCD_HEIGHT-20,WHITE);	//�����4
						tp_drawAdjustPoint(20,20,RED);//����1
						tp_printAdjustInfo(pos_temp, fac*100);
						continue;
					}
					tem1=abs(pos_temp[0][0]-pos_temp[2][0]);//x1-x3
					tem2=abs(pos_temp[0][1]-pos_temp[2][1]);//y1-y3
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);//�õ�1,3�ľ���

					tem1=abs(pos_temp[1][0]-pos_temp[3][0]);//x2-x4
					tem2=abs(pos_temp[1][1]-pos_temp[3][1]);//y2-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//�õ�2,4�ľ���
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05)//���ϸ�
					{
						cnt=0;
						tp_drawAdjustPoint(460,300,WHITE);	//�����4
						tp_drawAdjustPoint(20,20,RED);//����1
						tp_printAdjustInfo(pos_temp, fac*100);
						//tp_showAdjustInfo(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//��ʾ����   
						continue;
					}//��ȷ��

					//�Խ������
					tem1=abs(pos_temp[1][0]-pos_temp[2][0]);//x1-x3
					tem2=abs(pos_temp[1][1]-pos_temp[2][1]);//y1-y3
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);//�õ�1,4�ľ���

					tem1=abs(pos_temp[0][0]-pos_temp[3][0]);//x2-x4
					tem2=abs(pos_temp[0][1]-pos_temp[3][1]);//y2-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//�õ�2,3�ľ���
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05)//���ϸ�
					{
						cnt=0;
						tp_drawAdjustPoint(460,300,WHITE);	//�����4
						tp_drawAdjustPoint(20,20,RED);//����1
						tp_printAdjustInfo(pos_temp, fac*100);
						//tp_showAdjustInfo(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//��ʾ����   
						continue;
					}//��ȷ��
					//������
					t_pad.xfac=(float)(LCD_WIDTH-40)/(pos_temp[1][0]-pos_temp[0][0]);//�õ�xfac		 
					t_pad.xoff=(LCD_WIDTH-t_pad.xfac*(pos_temp[1][0]+pos_temp[0][0]))/2;//�õ�xoff

					t_pad.yfac=(float)(LCD_HEIGHT-40)/(pos_temp[2][1]-pos_temp[0][1]);//�õ�yfac
					t_pad.yoff=(LCD_HEIGHT-t_pad.yfac*(pos_temp[2][1]+pos_temp[0][1]))/2;//�õ�yoff  
					if(abs(t_pad.xfac)>2||abs(t_pad.yfac)>2)//������Ԥ����෴��.
					{
						cnt=0;
						briupLcdClear(WHITE);
						lcdDrawStr(100,120, (u8*)"Adjust Failed, Try Again!", &pen);
						tp_drawAdjustPoint(LCD_WIDTH-20,LCD_HEIGHT-20,WHITE);	//�����4
						tp_drawAdjustPoint(20,20,RED);								//����1

						t_pad.direct = (t_pad.direct==P_DIR_HOR)? P_DIR_VER:P_DIR_HOR;//�޸Ĵ�������.
						if(t_pad.direct)//X,Y��������Ļ�෴
						{
							t_pad.cmdRdx = 0x90;
							t_pad.cmdRdy = 0xD0; 
						}else				   //X,Y��������Ļ��ͬ
						{
							t_pad.cmdRdx = 0xD0;
							t_pad.cmdRdy = 0x90; 
						}			    
						continue;
					}		
					briupLcdClear(WHITE);//����
					lcdDrawStr(100,120, (u8*)"Adjust OK!", &pen);
#if	1 //TP_DEBIG_ENABLE
					printf("xfac: %f, xoff: %d\r\n", t_pad.xfac, t_pad.xoff);
					printf("yfac: %f, yoff: %d\r\n", t_pad.yfac, t_pad.yoff);
#endif				
					delayMs(1000);  
					briupLcdClear(WHITE);//����   
					return 0;//У�����				 
			}
		}
		delayMs(10);
		outtime++;
		if(outtime>1000)
		{
			briupLcdClear(WHITE);
			lcdDrawStr(100, 120, (u8*)"Adjust timeout.", &pen);
			delayMs(1000);
			briupLcdClear(WHITE);
			break;
		} 
	}
	return 0;
}

u8 tp_printAdjustInfo(u16 pos[][2], u16 fac)
{
	printf("x1 = %d, y1 = %d\r\n", pos[0][0], pos[0][1]);
	printf("x2 = %d, y2 = %d\r\n", pos[1][0], pos[1][1]);
	printf("x3 = %d, y3 = %d\r\n", pos[2][0], pos[2][1]);
	printf("x4 = %d, y4 = %d\r\n", pos[3][0], pos[3][1]);
	printf("fac = %d\r\n", fac);
	return 0;
}
//��ȡ����ֵ
u8	tp_getXandY(u16* x, u16* y)
{
#if USE_HORIZONTAL
	u8 i = tp_scan(1);
	*x = t_pad.currX*t_pad.xfac+t_pad.xoff;
	*y = t_pad.currY*t_pad.yfac+t_pad.yoff;
	return i;
#else
	u8 i = tp_scan(1);
	*y = t_pad.currX*t_pad.xfac+t_pad.xoff;
	*x = 320-(t_pad.currY*t_pad.yfac+t_pad.yoff);
	return i;
#endif
}

void tp_screenTrack(void)
{
	u16 x, y;
	LcdPen pen;
	pen.color = RED;
	pen.p_size = P_S16;
	pen.brush = P_SET_BRUSH;
	pen.direct = P_DIR_VER;
	
	//���Ƶ�ɫ��
	drawToolPad();
	
	while(1)
	{
		if(t_pad.scan(1))
		{
			x = t_pad.currX*t_pad.xfac+t_pad.xoff;
			y = t_pad.currY*t_pad.yfac+t_pad.yoff;
			if( x == 0 && y == 0)
				continue;
			if(x<LCD_WIDTH&&y<LCD_HEIGHT)
			{
				if(y>16)
				{
					lcdDrawBigPoint(x, y, &pen);
				}
				else
				{
					if(x>(LCD_WIDTH-32))
					{
						pen.color = WHITE;
						//lcdDrawRect(0, 17, 480, 302, &pen);
						lcdDrawRect(0, 17, 480, 100, &pen);
						lcdDrawRect(0, 117, 480, 100, &pen);
						lcdDrawRect(0, 217, 480, 103, &pen);
					}
					else if(x<(1*32))
					{
						pen.color = RED;
					}
					else if(x>(1*32)&&x<(2*32))
					{
						pen.color = BLUE;
					}
					else if(x>(2*32)&&x<(3*32))
					{
						pen.color = GREEN;
					}
					else if(x>(3*32)&&x<(4*32))
					{
						pen.color = BLACK;
					}
					else if(x>(4*32)&&x<(5*32))
					{
						pen.color = YELLOW;
					}
					else if(x>(5*32)&&x<(6*32))
					{
						pen.color = GRED;
					}
					else if(x>(6*32)&&x<(7*32))
					{
						pen.color = WHITE;
					}
				}
			}
		}
		else
		{
			delayMs(5);
		}
	}
}

//���ƹ������
void drawToolPad(void)
{
	LcdPen pen;
	pen.color = RED;
	pen.p_size = P_S16;
	pen.brush = P_SET_BRUSH;
	pen.direct = P_DIR_HOR;
	
	pen.color = RED;
	lcdDrawRect(32*0, 0, 32, 16, &pen);
	pen.color = BLUE;
	lcdDrawRect(32*1, 0, 32, 16, &pen);
	pen.color = GREEN;
	lcdDrawRect(32*2, 0, 32, 16, &pen);
	pen.color = BLACK;
	lcdDrawRect(32*3, 0, 32, 16, &pen);
	pen.color = YELLOW;
	lcdDrawRect(32*4, 0, 32, 16, &pen);
	pen.color = GRED;
	lcdDrawRect(32*5, 0, 32, 16, &pen);
	pen.color = WHITE;
	lcdDrawRect(32*6, 0, 32, 16, &pen);
	pen.color = BLUE;
	lcdDrawStr(LCD_WIDTH-40, 0, (u8*)"Clear", &pen);	
}

