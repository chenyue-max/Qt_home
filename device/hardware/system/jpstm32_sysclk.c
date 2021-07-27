/*************************************************************
 * File name: jpstm32_sysclk.c
 * Author: Duke An
 * Version: 0.1
 * Date: 201510
 * Description: ϵͳʱ�Ӳ���Դ�ļ�
 * Copyright @ 2013 by Briup Technology,Inc. All rights Reserved.
 *************************************************************/
#include "jpstm32_sysclk.h"
#include "jpstm32_nvic.h"
//#include "includes.h"
 
 
//us��ʱ������			   
static u8  fac_us=0;
//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��
static u16 fac_ms=0;

//RCCϵ�мĴ�����ʼ��
static void rccInit(void); 

//���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
#ifdef OS_CRITICAL_METHOD 	
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	SysTick_Handler
 * Description: systick �жϷ������
 * Input: NULL
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SysTick_Handler(void)
{				   
	OSIntEnter();		//�����ж�
	OSTimeTick();       //����ucos��ʱ�ӷ������               
	OSIntExit();        //���������л����ж�
}
#endif


 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	RccInit
 * Description: ��λϵͳʱ��
 * Input: NULL
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static void rccInit(void)
{
		RCC->APB1RSTR	= 0x00000000;
		RCC->APB2RSTR = 0x00000000;
		//�����SRAMʱ��ʹ�ܣ������ر�
		//AHB��λ
		RCC->AHBENR 	= 0x00000014;
		//����ʱ�ӹر�
		RCC->APB2ENR 	= 0x00000000;
		RCC->APB1ENR 	= 0x00000000;
		//ʹ���ڲ�����ʱ��
		RCC->CR 	|= 0x00000001;
		//��λSW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0]
		//ADCPRE[1:0],MCO[2:0]	
		RCC->CFGR &= 0xF8FF0000;
		//��λHSEON��CSSON��PLLON
		RCC->CR 	&= 0xFEF6FFFF;
		//��λHSEBYP
		RCC->CR 	&= 0xFFFBFFFF;	 
		//��λPLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE 
		RCC->CFGR &= 0xFF80FFFF;  
		//�ر������ж�
		RCC->CIR 	= 0x00000000; 
		//�����������ַ
		nvicSetVector(NVIC_VectTab_FLASH, 0x0);
}

 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	SysclkInit
 * Description: ��ʼ��ϵͳʱ��
 * Input: 
 *	>PLL, ��Ƶ
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
extern void sysclkInit(u8 PLL)
{
		rccInit();//��λʱ��
		RCC->CR |= 0x00010000;//�ⲿ����ʱ��ʹ��
		while(!(RCC->CR>>17));//�ȴ��ⲿʱ�Ӿ���
		//HCLK 2��Ƶ
		RCC->CFGR = 0x00000400;
		PLL -= 2;
		//PLL 9��Ƶ���-->72MHz
		RCC->CFGR 	|= PLL<<18;
		//HSEʱ����ΪPLL���
		RCC->CFGR 	|= 1<<16;
		//Prefetch buffer enable ����FLASH�ķ���Ƶ��
		FLASH->ACR 	|= 0x32;
		//����PLL
		RCC->CR 		|= 0x01000000;
		//�ȴ�PLL����
		while(!(RCC->CR>>25));
		//����PLLΪ��ǰϵͳʱ��
		RCC->CFGR |=0x00000002;
		//�鿴��ǰϵͳʱ���л�״̬�����RCC->CR��[3:2]
	
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	delayInit
 * Description: 
 *	>��ʱ���ܳ�ʼ��,��ʹ��ucos��ʱ��,
 *	>�˺������ʼ��ucos��ʱ�ӽ���
 * Input: 
 *	>SYSCLK ϵͳʱ��Ƶ��,�˿�ָ���Ǳ�Ƶ֮���Ƶ��,����Ƶ
 *	 ��ǰϵͳ��Ӧ����72 ��ʾ72MHz
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void delayInit(u8 SYSCLK)
{
	//���ʹ����ucosII
#ifdef OS_CRITICAL_METHOD 	
	u32 reload;
#endif
	//SYSTICKʹ���ⲿʱ��Դ	 
	SysTick->CTRL&=~(1<<2);	
	//�����Ƿ�ʹ��ucos,fac_us����Ҫʹ��
	fac_us=SYSCLK/8;		

	//���ʹ����ucosII
#ifdef OS_CRITICAL_METHOD 	
	//ÿ���ӵļ������� ��λΪM 
	reload=SYSCLK/8;		
	//����OS_TICKS_PER_SEC�趨���ʱ��
	//reloadΪ24λ�Ĵ���,���ֵ:16777216,��72M��,Լ��1.86s����	
	reload*=1000000/OS_TICKS_PER_SEC;
	//����ucos������ʱ�����ٵ�λ	   
	fac_ms=1000/OS_TICKS_PER_SEC;
	//����SYSTICK�ж�
	SysTick->CTRL |= 1<<1;
	//ÿ1/OS_TICKS_PER_SEC���ж�һ��	
	SysTick->LOAD=reload; 	
	//����SYSTICK    
	SysTick->CTRL |= 1<<0;
#else
	//��ucos��,����ÿ��ms��Ҫ��systickʱ����   
	fac_ms=(u16)fac_us*1000;
#endif
}	

//���ʹ����ucosII
#ifdef OS_CRITICAL_METHOD
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	_delay_us
 * Description: 
 *	>΢�뼶��ʱ����
 * Input: 
 *	>��ʱ��΢����
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void delayUs(u32 nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;	//LOAD��ֵ	    	 
	ticks=nus*fac_us; 			//��Ҫ�Ľ�����	  		 
	tcnt=0;
	OSSchedLock();				//��ֹucos���ȣ���ֹ���us��ʱ
	told=SysTick->VAL;        	//�ս���ʱ�ļ�����ֵ
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
			if(tnow<told)
			{
				tcnt+=told-tnow;
			} 
			else 
			{
				tcnt+=reload-tnow+told;	    
			}
			told=tnow;
			//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
			if(tcnt>=ticks)
			{
				break;
			}
		}  
	}
	OSSchedUnlock();			//����ucos���� 									    
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	_delay_ms
 * Description: 
 *	>���뼶��ʱ����
 * Input: 
 *	>��ʱ�ĺ�����
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void delayMs(u16 nms)
{	
	//���os�Ѿ�������	    
	if(OSRunning==TRUE)
	{		  
		//��ʱ��ʱ�����ucos������ʱ������ 
		if(nms>=fac_ms)
		{
			//ucos��ʱ
			OSTimeDly(nms/fac_ms);
		}
		//ucos�Ѿ��޷��ṩ��ôС����ʱ��,������ͨ��ʽ��ʱ    
		nms%=fac_ms;
	}
	delayUs((u32)(nms*1000));	//��ͨ��ʽ��ʱ 
}

#else//����ucosʱ
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	_delay_us
 * Description: 
 *	>΢�뼶��ʱ����
 * Input: 
 *	>��ʱ��΢����
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void delayUs(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL=0x01 ;      //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	} while((temp&0x01)&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function:	_delay_ms
 * Description: 
 *	>���뼶��ʱ����
 * Input: 
 *	>��ʱ�ĺ����� 
 *	>ע��nms�ķ�Χ SysTick->LOADΪ24λ�Ĵ���
 *	>����,�����ʱΪ: nms<=0xffffff*8*1000/SYSCLK 
 *	>SYSCLK��λΪHz,nms��λΪms ��72M������,nms<=1864 
 * Output: NULL
 * Return: NULL
 * Others: NULL
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void delayMs(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL=0x01 ;          //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	  	    
}
#endif
