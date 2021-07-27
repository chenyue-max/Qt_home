#ifndef  __DELAY_H_
#define __DELAY_H_
#include <stm32f10x_map.h>



extern void _delay_init(u8 SYSCLK);
extern void _delay_ms(u16 ms);
extern void _delay_us(u32 us);

#endif
