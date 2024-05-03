/*
 * @Author: xuanxie xiexuanlinux@126.com
 * @Date: 2024-05-04 02:03:34
 * @LastEditors: xuanxie xiexuanlinux@126.com
 * @LastEditTime: 2024-05-04 02:19:29
 * @FilePath: \STM32Panel\BSP\src\Public.c
 * @Description: 
 * 
 * Copyright (c) 2024 by xiexuan , All Rights Reserved. 
 */
#include "Public.h"



void OS_Init(void)
{
    
    // SysTick_Init(72);
    
    while( SysTick_Config(SystemCoreClock_KHZ));	//配置参数为多少个Tciks。配置成功返回0，否则进入while死循环。
    // LED_GPIOInit();
}
