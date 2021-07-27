#ifndef __RC522_H
#define __RC522_H

#include "sys.h"
#include "jpstm32_gpio.h"
/////////////////////////////////////////////////////////////////////
//MF522������
/////////////////////////////////////////////////////////////////////
#define PCD_IDLE              0x00               //ȡ����ǰ����
#define PCD_AUTHENT           0x0E               //��֤��Կ
#define PCD_RECEIVE           0x08               //��������
#define PCD_TRANSMIT          0x04               //��������
#define PCD_TRANSCEIVE        0x0C               //���Ͳ���������
#define PCD_RESETPHASE        0x0F               //��λ
#define PCD_CALCCRC           0x03               //CRC����

/////////////////////////////////////////////////////////////////////
//Mifare_One��Ƭ������
/////////////////////////////////////////////////////////////////////
#define PICC_REQIDL           0x26               //Ѱ��������δ��������״̬
#define PICC_REQALL           0x52               //Ѱ��������ȫ����
#define PICC_ANTICOLL1        0x93               //����ײ
#define PICC_ANTICOLL2        0x95               //����ײ
#define PICC_AUTHENT1A        0x60               //��֤A��Կ
#define PICC_AUTHENT1B        0x61               //��֤B��Կ
#define PICC_READ             0x30               //����
#define PICC_WRITE            0xA0               //д��
#define PICC_DECREMENT        0xC0               //�ۿ�
#define PICC_INCREMENT        0xC1               //��ֵ
#define PICC_RESTORE          0xC2               //�������ݵ�������
#define PICC_TRANSFER         0xB0               //���滺����������
#define PICC_HALT             0x50               //����

/////////////////////////////////////////////////////////////////////
//MF522 FIFO���ȶ���
/////////////////////////////////////////////////////////////////////
#define DEF_FIFO_LENGTH       64                 //FIFO size=64byte
#define MAXRLEN  18

/////////////////////////////////////////////////////////////////////
//MF522�Ĵ�������
/////////////////////////////////////////////////////////////////////
// PAGE 0
#define     RFU00                 0x00    //���ܴ���һ��ʹ��
#define     CommandReg            0x01    //��ʼ�ͽ����������
#define     ComIEnReg             0x02    //ͨ��������ʹ���ж�
#define     DivlEnReg             0x03    //ͬ��
#define     ComIrqReg             0x04    //�ж�����λ
#define     DivIrqReg             0x05		//ͬ��
#define     ErrorReg              0x06    
#define     Status1Reg            0x07    
#define     Status2Reg            0x08    
#define     FIFODataReg           0x09     //���벢��64λ�����������64λ����
#define     FIFOLevelReg          0x0A
#define     WaterLevelReg         0x0B
#define     ControlReg            0x0C
#define     BitFramingReg         0x0D
#define     CollReg               0x0E
#define     RFU0F                 0x0F
// PAGE 1     
#define     RFU10                 0x10
#define     ModeReg               0x11
#define     TxModeReg             0x12
#define     RxModeReg             0x13
#define     TxControlReg          0x14
#define     TxAutoReg             0x15
#define     TxSelReg              0x16
#define     RxSelReg              0x17
#define     RxThresholdReg        0x18
#define     DemodReg              0x19
#define     RFU1A                 0x1A
#define     RFU1B                 0x1B
#define     MifareReg             0x1C
#define     RFU1D                 0x1D
#define     RFU1E                 0x1E
#define     SerialSpeedReg        0x1F
// PAGE 2    
#define     RFU20                 0x20  
#define     CRCResultRegM         0x21
#define     CRCResultRegL         0x22
#define     RFU23                 0x23
#define     ModWidthReg           0x24
#define     RFU25                 0x25
#define     RFCfgReg              0x26
#define     GsNReg                0x27
#define     CWGsCfgReg            0x28
#define     ModGsCfgReg           0x29
#define     TModeReg              0x2A
#define     TPrescalerReg         0x2B
#define     TReloadRegH           0x2C
#define     TReloadRegL           0x2D
#define     TCounterValueRegH     0x2E
#define     TCounterValueRegL     0x2F
// PAGE 3      
#define     RFU30                 0x30
#define     TestSel1Reg           0x31
#define     TestSel2Reg           0x32
#define     TestPinEnReg          0x33
#define     TestPinValueReg       0x34
#define     TestBusReg            0x35
#define     AutoTestReg           0x36
#define     VersionReg            0x37
#define     AnalogTestReg         0x38
#define     TestDAC1Reg           0x39  
#define     TestDAC2Reg           0x3A   
#define     TestADCReg            0x3B   
#define     RFU3C                 0x3C   
#define     RFU3D                 0x3D   
#define     RFU3E                 0x3E   
#define     RFU3F		  		  0x3F

/////////////////////////////////////////////////////////////////////
//��MF522ͨѶʱ���صĴ������
/////////////////////////////////////////////////////////////////////
#define 	MI_OK                 0
#define 	MI_NOTAGERR           (1)
#define 	MI_ERR                (2)

#define	SHAQU1		0X01
#define	KUAI4			0X04
#define	KUAI7			0X07
#define	REGCARD		0xa1
#define	CONSUME		0xa2
// #define READCARD	0xa3
#define ADDMONEY	0xa4

/**************************
         ����IO��
**************************/
//#define SET_SPI_CS  	GPIOA->BSRR=0X8000	//��GPIOA port 15��Ϊ�ߵ�ƽ(PA15=1)
//#define CLR_SPI_CS  	GPIOA->BRR=0X8000	  //��GPIOA port 15��Ϊ�͵�ƽ(PA15=0)
//#define SET_RC522RST  GPIOE->BSRR=0X20	//��GPIOE port 5��Ϊ�ߵ�ƽ(PE5=1)
//#define CLR_RC522RST  GPIOE->BRR=0X20	  //��GPIOE port 5��Ϊ�͵�ƽ(PE5=0)

#define SET_SPI_CS  		PAxOut(4)=1		//��PA4��Ϊ�ߵ�ƽ(PA4=1)
#define CLR_SPI_CS  		PAxOut(4)=0	  //��PA4��Ϊ�͵�ƽ(PA4=0)
#define SET_RC522RST  	PBxOut(1)=1		//��PB1��Ϊ�ߵ�ƽ(PB1=1)
#define CLR_RC522RST  	PBxOut(1)=0	  //��PB1��Ϊ�͵�ƽ(PB1=0)

#define SPIReadByte()	SPIWriteByte(0)
u8 SPIWriteByte(u8 byte);
void SPI3_Init(void);
void delay_ns(u32 ns);                  //��ʱ


/**************************
    RC522������������
**************************/

void InitRc522(void);																//��    �ܣ�RC522��Ƶ��ģ���ʼ��
void ClearBitMask(u8   reg,u8   mask);							//��    �ܣ���RC522�Ĵ���λ
void WriteRawRC(u8   Address, u8   value);					//��    �ܣ�дRC632�Ĵ���
void SetBitMask(u8   reg,u8   mask);								//��    �ܣ���RC522�Ĵ���λ
char PcdComMF522(u8   Command, 
                 u8 *pIn , 
                 u8   InLenByte,
                 u8 *pOut , 
                 u8  *pOutLenBit);									//��    �ܣ�ͨ��RC522��ISO14443��ͨѶ
void CalulateCRC(u8 *pIn ,u8   len,u8 *pOut );			//��    �ܣ���MF522����CRC16����
u8 ReadRawRC(u8   Address);													//��    �ܣ���RC632�Ĵ���


char PcdReset(void);																						//��    �ܣ���λRC522
char PcdRequest(unsigned char req_code,unsigned char *pTagType);//��    �ܣ�Ѱ��
void PcdAntennaOn(void);																				//��    �ܣ��������� 
void PcdAntennaOff(void);																				//��    �ܣ��ر�����
char M500PcdConfigISOType(unsigned char type);									//��    �ܣ�����RC632�Ĺ�����ʽ 
char PcdAnticoll(unsigned char *pSnr);													//��    �ܣ�����ײ
char PcdSelect(unsigned char *pSnr);														//��    �ܣ�ѡ����Ƭ
char PcdAuthState(unsigned char auth_mode,unsigned char addr,unsigned char *pKey,unsigned char *pSnr);//��    �ܣ���֤��Ƭ����
char PcdWrite(unsigned char addr,unsigned char *pData);					//��    �ܣ�д���ݵ�M1��һ��
char PcdRead(unsigned char addr,unsigned char *pData);					//��    �ܣ���ȡM1��һ������
char PcdHalt(void);																							//��    �ܣ����Ƭ��������״̬
void Reset_RC522(void);																					//��    �ܣ���λRC522


char PcdValue(u8 dd_mode,u8 addr,u8 *pValue);										//��		�ܣ���ֵ��ۿ�
char PcdBakValue(u8 sourceaddr, u8 goaladdr);										//��		�ܣ�����Ǯ��



#endif


