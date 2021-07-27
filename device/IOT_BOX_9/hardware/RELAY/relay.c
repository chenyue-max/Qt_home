
#include "relay.h"

void relay_init(void)
{
	RCC->APB2ENR |= 1<<2;
	GPIOA->CRL &= 0xFF00FFFF;
	GPIOA->CRL |= 0x00330000;
}


