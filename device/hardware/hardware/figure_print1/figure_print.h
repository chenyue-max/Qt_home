#ifndef __FIGURE_PRINT_H_
#define __FIGURE_PRINT_H_

#include <stm32f10x_map.h>
#include "usart3.h"
#include "beep.h"
#define Max_NUMBER 80




void figure_print_init();
unsigned char VefPSW(void);//验证握手指令，成功返回1
unsigned char Clear_ALL(void);//清除指纹库
unsigned char ImgProcess(unsigned char BUFID);//发送获取图像并生成特征文件，存入BUFID中
unsigned int Searchfinger(void);//搜索指纹(发送搜索命令、以及根据返回值确定是否存在)
unsigned int search(void);//
unsigned char savefingure(unsigned int ID);//保存指纹
unsigned char enroll(void);//采集两次指纹，生成一个指纹模板
void numshow(unsigned int num);

extern unsigned int 	SaveNumber; //每录入一次SaveNumber++
extern unsigned int    searchnum;
extern unsigned int  	SearchNumber;
extern unsigned char changeflag,modeflag,clearallflag;  


#endif
