#ifndef __FIGURE_PRINT_H_
#define __FIGURE_PRINT_H_

#include <stm32f10x_map.h>



void input_figure(void);
int check_figure(void);
void figure_print_init(void);
unsigned char VefPSW(void);//��֤����ָ��ɹ�����1
unsigned char Clear_ALL(void);//���ָ�ƿ�
unsigned char ImgProcess(unsigned char BUFID);//���ͻ�ȡͼ�����������ļ�������BUFID��
unsigned int search(void);//
unsigned char savefingure(unsigned int ID);//����ָ��
unsigned char enroll(void);//�ɼ�����ָ�ƣ�����һ��ָ��ģ��
void numshow(unsigned int num);

extern unsigned int 	SaveNumber; //ÿ¼��һ��SaveNumber++
extern unsigned int    searchnum;
extern unsigned int  	SearchNumber;


#endif
