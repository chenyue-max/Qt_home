#ifndef __RC522_ADD_H
#define __RC522_ADD_H

#include "sys.h"


//��������ĺ궨��
#define  READCARD   0xA1
#define  WRITECARD  0xA2
#define  KEYCARD    0xA3
#define  SETTIME    0xA4
#define  SENDID     0xA5




//����������ݵĶ���
extern u16  KuaiN;//��ʾҪ���ʵĿ�
extern u8 oprationcard,bSendID;
extern u8 Read_Data[16],PassWd[6],WriteData[16],RevBuffer[30], MLastSelectedSnr[4],NewKey[16];	
// extern char cardID[4];//����
extern u8 cardID[4];	//����
extern u8 flag_com;		//�Ѷ������ı�־

extern double temp_money;//������32λ��Ч���֣�����

extern u8 administrator[4];//����Ա����
extern u8 datatemp[4];	 //��AT24C02�������Ŀ���







/*���Լ���д���ǳ���Ҫ�ĺ���*/
void InitAlldata(void);					//��  ��  :  ��ʼ�����ж���������ݵ�����
void ctrlprocess(void);					//��  ��  :  ��Ѱ��������ײ��ѡ�������Ϳ��š�������д�����޸�������в���
void command_choose(u8 command);//��  ��  :  �жϲ������ͣ����Ϳ��š�������д�����޸����� ��
void RC522_work(void);					//��  ��  :  ÿ�������ζ�ʱ���жϣ���50ms����Բ�����������ѡ���жϣ�

void Read_cardID(void);							//������
double Read_overage(void);					//���������
void write_overage(double overage); //д�������

int Mult10(int n);							//��10��n�η�
void UART1_SendByte(u16 Data);	//���ڷ���һ���ֽڣ�2λ16��������
















/*��������*/
void ShowID(u16 x,u16 y, u8 *p, u16 charColor, u16 bkColor);	      //��ʾ���Ŀ��ţ���ʮ��������ʾ
void PutNum(u16 x,u16 y, u32 n1,u8 n0, u16 charColor, u16 bkColor);	//��ʾ����
void Store(u8 *p,u8 store,u8 cash);                                 //����Ҫ��һ������


#endif


