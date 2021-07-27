#ifndef __RUN_H__
#define __RUN_H__

#include "Debug_usart.h"
#include "ZigBee_usart.h"

#define board1 0
#define board2 1
#define board3 0
#define board4 0
#define board5 0
#define board6 0
#define board7 0
#define board8 0

#define BoxID  0x01//???????????

void interface_init(void);
void run(u8 device_id, u8* c_con);
//??????
void analysis(void);
//??ݷ??????
void response(u8 device_id, u8* buf);
#endif


