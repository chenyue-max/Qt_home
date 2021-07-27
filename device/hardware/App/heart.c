#include "heart.h"

#if BOARD1
void heart_up(void)
{

}
# endif

#if BOARD2
void heart_up(void)
{
  u8 con[1]={0x01};
  device_control(0x16,con);
  delayMs(800);
  device_control(0x17,con);
  delayMs(820);
  device_control(0x18,con);
  delayMs(850);
  device_control(0x19,con);
  delayMs(860);
  device_control(0x2C,con);
  delayMs(880);
}  
# endif

#if BOARD3
void heart_up(void)
{
	 u8 con[1]={0x01};
  device_control(0x1A,con);
  delayMs(800);
  device_control(0x1B,con);
  delayMs(820);
  device_control(0x1C,con);
  delayMs(850);
  device_control(0x1D,con);
  delayMs(860);


}
# endif

#if BOARD4
void heart_up(void)
{
		 u8 con[1]={0x01};
  device_control(0x1E,con);
  delayMs(800);
  device_control(0x1F,con);
  delayMs(820);
  device_control(0x20,con);
  delayMs(850);


}
# endif

#if BOARD5
void heart_up(void)
{
  u8 con[1]={0x01};
  device_control(0x23,con);
  delayMs(800);
  device_control(0x24,con);
  delayMs(820);
}
# endif

#if BOARD6
void heart_up(void)
{

}
# endif

#if BOARD7
void heart_up(void)
{
  
}
# endif

#if BOARD8
void heart_up(void)
{

}
# endif