/*
 * @Author: xuanxie xiexuanlinux@126.com
 * @Date: 2024-03-06 01:11:44
 * @LastEditors: xuanxie xiexuanlinux@126.com
 * @LastEditTime: 2024-04-29 01:55:44
 * @FilePath: \综合平台\USER\main.c
 * @Description: 
 * 
 * Copyright (c) 2024 by xiexuan , All Rights Reserved. 
 */

#include "stm32f10x.h"
#include "bit_band.h"
#include "task.h"
#include "pwm.h"
#include "usart.h"
#include "fifo.h"

FifoStructTypeDef FifoStruct1;
FifoStructTypeDef FifoStruct2;
int main(void)
{

    OS_Init();
    setGPIO_Init();
    USART_Main();
    TIM1_PWM_Init(1000,50);
    
    
    Task();
        
    
}
