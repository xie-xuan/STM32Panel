/*
 * @Author: xuanxie xiexuanlinux@126.com
 * @Date: 2024-03-06 01:33:51
 * @LastEditors: xuanxie xiexuanlinux@126.com
 * @LastEditTime: 2024-03-11 02:32:18
 * @FilePath: \PWM发波\APP\pwm.c
 * @Description: 
 * 
 * Copyright (c) 2024 by xiexuan , All Rights Reserved. 
 */
#include "pwm.h"




void TIM1_PWM_Init(uint32_t frequency, uint8_t dutyCycle) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    // 使能TIM1时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);
    // TIM1配置
    
    TIM_TimeBaseStructure.TIM_Prescaler = 71;  // 预分频值，时钟为72MHz，分频为72，得到1MHz的计数频率
    TIM_TimeBaseStructure.TIM_Period = 999;    // 计数器周期，1MHz计数频率下，周期为1000即1ms
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // 配置TIM1为PWM模式
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = (uint16_t)((dutyCycle / 100.0) * TIM_TimeBaseStructure.TIM_Period);
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);

    // 使能TIM1输出比较通道1
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_CtrlPWMOutputs(TIM2, ENABLE);   
    // 使能TIM1
    // TIM_Cmd(TIM2, ENABLE);
}


void setPWMFrequency(uint32_t frequency) {
    // 根据新的频率重新计算预分频值和周期
    uint32_t TIM2_CLK = SystemCoreClock_KHZ;  // 假设时钟频率为72MHz
    uint16_t prescaler = (uint16_t)(TIM2_CLK / frequency) - 1;

    TIM_PrescalerConfig(TIM2, prescaler, TIM_PSCReloadMode_Update);
}

void setPWMDutyCycle(uint8_t dutyCycle) {
    // 根据新的占空比重新设置脉冲值
    uint16_t pulse = (uint16_t)((dutyCycle / 100.0) * (TIM2->ARR));
    
    TIM_SetCompare3(TIM2, pulse);
}

void setGPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    // 使能GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 配置GPIOB引脚为复用推挽输出，对应TIM1通道1
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // 以PA8为例
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}
