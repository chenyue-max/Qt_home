#ifndef __SHT20_H
#define __SHT20_H
#include "myiic.h"

/*******************************
��������SHT20_Measure
�������ܣ���ȡ��ʪ������
��������ֵ���ɹ�����0
*******************************/
unsigned char SHT20_Measure(float* Temperature, float* Humidity);
/*******************************
��������SHT20_Original_TEMP
�������ܣ���ȡԭʼ�¶�����
��������ֵ���ɹ�����0
*******************************/
unsigned char SHT20_Original_TEMP(u16* Temperature);
/*******************************
��������SHT20_Original_HUM
�������ܣ���ȡԭʼʪ������
��������ֵ���ɹ�����0
*******************************/
unsigned char SHT20_Original_HUM(u16* Humidity);

#endif
