#ifndef __MALLOC_H
#define __MALLOC_H
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//�ڴ���� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
#define __SDIO_H_
#include "jpstm32_gpio.h"
#include "jpstm32_nvic.h"
#include "jpstm32_sysclk.h"
#include "sys.h"
#ifndef NULL
#define NULL 0
#endif

#define SRAMIN	0	//�ڲ��ڴ��
#define SRAMEX  1	//�ⲿ�ڴ��


//mem1�ڴ�����趨.mem1��ȫ�����ڲ�SRAM����
#define MEM1_BLOCK_SIZE			32  	  						//�ڴ���СΪ32�ֽ�
#define MEM1_MAX_SIZE			40*1024  						//�������ڴ� 40K
#define MEM1_ALLOC_TABLE_SIZE	MEM1_MAX_SIZE/MEM1_BLOCK_SIZE 	//�ڴ���С

//mem2�ڴ�����趨.mem2���ڴ�ش����ⲿSRAM����,�����Ĵ����ڲ�SRAM����
#define MEM2_BLOCK_SIZE			32  	  						//�ڴ���СΪ32�ֽ�
#define MEM2_MAX_SIZE			200*1024  						//�������ڴ�200K
#define MEM2_ALLOC_TABLE_SIZE	MEM2_MAX_SIZE/MEM2_BLOCK_SIZE 	//�ڴ���С
		 
		 
//�ڴ���������
struct _m_mallco_dev
{
	void (*init)(u8);					//��ʼ��
	u8 (*perused)(u8);		  	    	//�ڴ�ʹ����
	u8 	*membase[2];					//�ڴ�� ����2��������ڴ�
	u16 *memmap[2]; 					//�ڴ����״̬��
	u8  memrdy[2]; 						//�ڴ�����Ƿ����
};
extern struct _m_mallco_dev mallco_dev;	 //��mallco.c���涨��

void mymemset(void *s,u8 c,u32 count);	 //�����ڴ�
void mymemcpy(void *des,void *src,u32 n);//�����ڴ�     
void mem_init(u8 memx);					 //�ڴ�����ʼ������(��/�ڲ�����)
u32 mem_malloc(u8 memx,u32 size);		 //�ڴ����(�ڲ�����)
u8 mem_free(u8 memx,u32 offset);		 //�ڴ��ͷ�(�ڲ�����)
u8 mem_perused(u8 memx);				 //����ڴ�ʹ����(��/�ڲ�����) 
////////////////////////////////////////////////////////////////////////////////
//�û����ú���
void myfree(u8 memx,void *ptr);  			//�ڴ��ͷ�(�ⲿ����)
void *mymalloc(u8 memx,u32 size);			//�ڴ����(�ⲿ����)
void *myrealloc(u8 memx,void *ptr,u32 size);//���·����ڴ�(�ⲿ����)
#endif













