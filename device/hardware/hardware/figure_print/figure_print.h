#ifndef __FIGURE_PRINT_H_
#define __FIGURE_PRINT_H_

#include <stm32f10x_map.h>



void input_figure(void);
int check_figure(void);
void figure_print_init(void);
unsigned char VefPSW(void);//验证握手指令，成功返回1
unsigned char Clear_ALL(void);//清除指纹库
unsigned char ImgProcess(unsigned char BUFID);//发送获取图像并生成特征文件，存入BUFID中
unsigned int search(void);//
unsigned char savefingure(unsigned int ID);//保存指纹
unsigned char enroll(void);//采集两次指纹，生成一个指纹模板
void numshow(unsigned int num);

extern unsigned int 	SaveNumber; //每录入一次SaveNumber++
extern unsigned int    searchnum;
extern unsigned int  	SearchNumber;


#endif
