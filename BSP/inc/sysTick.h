#ifndef _sysTick_H
#define _sysTick_H

#include "stm32f10x.h"

#define SystemCoreClock_MHZ  (72)
#define SystemCoreClock_KHZ  (SystemCoreClock_MHZ*1000)

void SysTick_Init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);



#endif
