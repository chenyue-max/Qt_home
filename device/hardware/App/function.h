#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "sys.h"
#include "jpstm32_sysclk.h"
#include "jpstm32_gpio.h"
#include "ZigBee_usart.h"


#define BOARD1 0
#define BOARD2 0
#define BOARD3 0
#define BOARD4 1
#define BOARD5 0
#define BOARD6 0
#define BOARD7 0
#define BOARD8 0


#if BOARD1
#define NODE_ID 0x10
#endif

#if BOARD2
#define NODE_ID 0x20
#define TIME_h 50000
#endif

#if BOARD3
#define NODE_ID 0x30
#define TIME_h 110000
#endif

#if BOARD4
#define NODE_ID 0x40
#define TIME_h 17000
#endif

#if BOARD5
#define NODE_ID 0x50

#endif

#if BOARD6
#define NODE_ID 0x60

#endif

#if BOARD7
#define NODE_ID 0x70

#endif

#if BOARD8
#define NODE_ID 0x80

#endif

void device_init(void);
void device_control(u8 device_id,u8 *control);
void device_feedback(u8 data_len,u8 *data,u8 device_id);
void analysis(void);
	

#endif
