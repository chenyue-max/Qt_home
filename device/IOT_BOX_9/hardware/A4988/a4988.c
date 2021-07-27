#include "a4988.h"
/*
通信方式采用的是PWM
a4988使能端，低电平使能，硬件上就直接给接地
PB0 -> 驱动脉冲信号输入
PB9 -> 定时器4的pwm通道4
PB13-> DIR能改变电机的转动方向
PB8 -> SLEEP
PB7 -> RSSET复位
MS1,MS2，MS3对应细分设置，细分越高转动更慢，精度更高
MS1   MS2   MS3    细分数
0      0     0       1
1      0     0       2
0      1     0       4
1      1     0       8
1      1     1       16
*/

#include "a4988.h"
#include "jpstm32_gpio.h"

void tim4_tim3_init(void)
{
	RCC->APB2ENR |= 1<<3; //使能PB端口时钟
	RCC->APB2ENR |= 1<<2; //使能PA端口时钟
	RCC->APB1ENR |= (1<<1)|(1<<2);//使能定时器3，4时钟

	GPIOB->CRH &= 0xFFFFFF0F;
	GPIOB->CRH |= 0x000000B0;// 复用推完输出

	TIM3->PSC = 7199; //   72MHZ/7200 = 10^4  0.1ms
	TIM3->ARR = 99;//重装值 
	TIM3->CR1 |= 0<<4;//向上计数
	TIM3->CR1 |= 1<<3;//设置TIM3单脉冲模式
	TIM3->CR2 |= 4<<4;//单一模式下不需要进行设置
	TIM3->CCMR1 |= 1<<3; //使能定时器3的通道1的预装载器
	TIM3->CCMR1 |= 7<<4; //向上计数时，当前数值大于预装载值，有效电平为1
	TIM3->CCER |= 0<<1;//有效电平为高电平
	TIM3->CCR1 = 20;
	TIM3->DIER |= 1<<0;//允许更新中断
	TIM3->CR1 |= 1<<0;//使能定时器3

	TIM4->CR1 |= 0<<4;//向上计数
	TIM4->PSC = 719;//预分频
	TIM4->ARR = 29;
	
	TIM4->SMCR |= 5;//门控模式
	TIM4->SMCR |= 1<<7;//使能TIM4的主从模式
	TIM4->SMCR |= 2<<4;//TIM3为主设备，TIM4从设备

	TIM4->CCMR2 |= 1<<11;//使能定时器4的通道4预装载寄存器
	TIM4->CCMR2 |= 7<<12;//向上计数，有效电平为 1
	TIM4->CCER |= 1<<12;//OC1输出使能
	TIM4->CCER |= 0<<13;//有效电平为高
	TIM4->CCR4 = 15;//占空比一半
	TIM4->CR1 |= 1<<0;//使能
	MY_NVIC_Init(2,3,TIM3_IRQChannel,2);
}

void TIM3_IRQHandler()
{
	if(TIM3->SR & 0x0001)
	{
		A4988_EN = 1;//除能
	}
	TIM3->SR &= ~(1<<0);//清除中断标记位
}

/*
	cycle 是一个tim3的脉冲周期单位us
	pulse_num 是脉冲个数，决定了步进电机的步数
	步数最大65535是因为u16的限制。
	但是因为它在滑杆上所以最远能走380
*/
void motor_control(u16 cycle, u16 pulse_num)
{
	u16 arr3 = 0;
	u32 time = 0;
	A4988_EN = 0;//使能步进电机驱动

	if(pulse_num)
	{
		time = cycle*pulse_num/100;//预防720， 100us计数一次
		arr3 = cycle/10 ;//预分频 72 10us 计数一次
		TIM3->ARR = time+1;
		TIM3->CCR1 = 1;

		TIM4->ARR = arr3;
		TIM4->CCR4 = arr3/2;
		TIM4->CNT = 0;
		TIM3->CR1 |= 1<<0; //使能TIM3
	}

}


void a4988_init(void)
{
	RCC->APB2ENR |= 1<<3; //开启GPIOB的端口
	GPIOB->CRL &= 0x000FFF00;
	GPIOB->CRL |= 0x33300033;
	GPIOB->CRH &= 0xFF0FFFF0;
	GPIOB->CRH |= 0x00300003;//设置引脚推挽输出
	tim4_tim3_init();
	//初始化脉冲信号
	A4988_EN = 1;//使能输出。 1是不使能， 0使能
	//设置细分 
	A4988_MS1 = 0;
	A4988_MS2 = 0;
	A4988_MS3 = 0;
	//设置初始方向
	A4988_DIR = 1;//前

	//默认为不工作
	A4988_SLEEP = 1;
	A4988_RESET = 1;
}

