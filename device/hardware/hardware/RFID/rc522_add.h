#ifndef __RC522_ADD_H
#define __RC522_ADD_H

#include "sys.h"


//操作命令的宏定义
#define  READCARD   0xA1
#define  WRITECARD  0xA2
#define  KEYCARD    0xA3
#define  SETTIME    0xA4
#define  SENDID     0xA5




//读卡相关数据的定义
extern u16  KuaiN;//表示要访问的块
extern u8 oprationcard,bSendID;
extern u8 Read_Data[16],PassWd[6],WriteData[16],RevBuffer[30], MLastSelectedSnr[4],NewKey[16];	
// extern char cardID[4];//卡号
extern u8 cardID[4];	//卡号
extern u8 flag_com;		//已读到卡的标志

extern double temp_money;//卡内余额（32位有效数字？？）

extern u8 administrator[4];//管理员卡号
extern u8 datatemp[4];	 //从AT24C02读出来的卡号







/*（自己编写）非常重要的函数*/
void InitAlldata(void);					//描  述  :  初始化所有读卡相关数据的设置
void ctrlprocess(void);					//描  述  :  对寻卡、防冲撞、选卡、发送卡号、读卡、写卡、修改密码进行操作
void command_choose(u8 command);//描  述  :  判断操作类型（发送卡号、读卡、写卡、修改密码 ）
void RC522_work(void);					//描  述  :  每进入两次定时器中断（即50ms）则对操作类型重新选择（判断）

void Read_cardID(void);							//读卡号
double Read_overage(void);					//读卡内余额
void write_overage(double overage); //写卡内余额

int Mult10(int n);							//求10的n次方
void UART1_SendByte(u16 Data);	//串口发送一个字节（2位16进制数）
















/*函数声明*/
void ShowID(u16 x,u16 y, u8 *p, u16 charColor, u16 bkColor);	      //显示卡的卡号，以十六进制显示
void PutNum(u16 x,u16 y, u32 n1,u8 n0, u16 charColor, u16 bkColor);	//显示余额函数
void Store(u8 *p,u8 store,u8 cash);                                 //最重要的一个函数


#endif


