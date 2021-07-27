
#include "briupFSMC.h"
#include "jpstm32_sysclk.h"
void briupFSMCInit(void)
{
	//ʹ��FSMC
	RCC->AHBENR |= 1<<8;
	//ʹ��GPIOB/D/E/G
	RCC->APB2ENR |= 1<<3| 1<<5 | 1<<6 | 1<<8;
	
	//PB�˿����ţ�
	//	LCD����
	GPIOB->CRL &= ~0x0f;
	GPIOB->CRL|= 0x03;
	
	//PD�˿����ţ�
	//	PD.0/1 -> FSMC_D2/3		PD.4/5 -> FSMC_NOE/NWE ���ʹ�ܡ�дʹ��
	//	PD.8/9/10/14/15 -> FSMC_D13/14/15/0/1
	GPIOD->CRL &= 0xff00ff00;
	GPIOD->CRL |= 0x00BB00BB;
	GPIOD->CRH &= 0x00fff000;
	GPIOD->CRH |= 0xBB000BBB;
	
	//PE�˿�����
	//	PE.7~15 -> FSMC_D4~12
	GPIOE->CRL &= 0x0fffffff;
	GPIOE->CRL |= 0xB0000000;
	GPIOE->CRH  = 0xBBBBBBBB;
	
	//PG�˿�����
	//	PG.0 -> A10(��ַ��)	PG.12 -> NE4(�洢��Ƭѡ��)
	GPIOG->CRL &= ~0x0f;
	GPIOG->CRL |= 0x0B;
	GPIOG->CRH &= 0xfff0ffff;
	GPIOG->CRH |= 0x000B0000;
	
	//============================
	//		FSMC�Ĵ�������
	//���Bank1Area4��Ӧ�Ĵ���������
	FSMC_Bank1->BTCR[6] = 0;	//FSMC_BCR4	�Ĵ���
	FSMC_Bank1->BTCR[7] = 0;	//FSMC_BTR4	�Ĵ���
	FSMC_Bank1E->BWTR[6] = 0;	//FSMC_BWTR4�Ĵ���
	
	FSMC_Bank1->BTCR[6] = 1<<14 | 1<<12 | 1<<4;
	FSMC_Bank1->BTCR[7] = 0x0f<<8 | 0x01;
	
	FSMC_Bank1E->BWTR[6] = 0x03<<8;
	
	FSMC_Bank1->BTCR[6] |= 0x01;
	delayMs(50);
}

