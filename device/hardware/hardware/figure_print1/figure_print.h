#ifndef __FIGURE_PRINT_H_
#define __FIGURE_PRINT_H_

#include <stm32f10x_map.h>
#include "usart3.h"
#include "beep.h"
#define Max_NUMBER 80




void figure_print_init();
unsigned char VefPSW(void);//��֤����ָ��ɹ�����1
unsigned char Clear_ALL(void);//���ָ�ƿ�
unsigned char ImgProcess(unsigned char BUFID);//���ͻ�ȡͼ�����������ļ�������BUFID��
unsigned int Searchfinger(void);//����ָ��(������������Լ����ݷ���ֵȷ���Ƿ����)
unsigned int search(void);//
unsigned char savefingure(unsigned int ID);//����ָ��
unsigned char enroll(void);//�ɼ�����ָ�ƣ�����һ��ָ��ģ��
void numshow(unsigned int num);

extern unsigned int 	SaveNumber; //ÿ¼��һ��SaveNumber++
extern unsigned int    searchnum;
extern unsigned int  	SearchNumber;
extern unsigned char changeflag,modeflag,clearallflag;  


#endif
