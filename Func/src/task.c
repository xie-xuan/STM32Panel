/*
 * @Author: xuanxie xiexuanlinux@126.com
 * @Date: 2024-03-06 01:11:44
 * @LastEditors: xuanxie xiexuanlinux@126.com
 * @LastEditTime: 2024-04-29 02:46:08
 * @FilePath: \综合平台\BSP\src\task.c
 * @Description: 
 * 
 * Copyright (c) 2024 by xiexuan , All Rights Reserved. 
 */
#include "task.h"


volatile uint8_t Task_1ms_Flag = 0;
volatile uint8_t Task_2ms_Flag = 0;
volatile uint8_t Task_5ms_Flag = 0;
volatile uint8_t Task_10ms_Flag = 0;
volatile uint8_t Task_50ms_Flag = 0;

u16 g_u16Timecount=0;
u16 g_u16duty = 50;
u16 g_u16frq = 1000;



void Task(void)
{
    static u16 g_u16Timecountold = 0;
    while(1)
    {
        
        if(g_u16Timecountold != g_u16Timecount)
        {
            if (g_u16Timecount % 1 == 0) {
                Task_1ms_Flag = 1;
            }
            if (g_u16Timecount % 2 == 0) {
                Task_2ms_Flag = 1;
            }
            if (g_u16Timecount % 5 == 0) {
                Task_5ms_Flag = 1;
            }
            if (g_u16Timecount % 10 == 0) {
                Task_10ms_Flag = 1;
            }
            if (g_u16Timecount % 50 == 0) {
                Task_50ms_Flag = 1;
            }

            
            
            g_u16Timecountold = g_u16Timecount;
        }
        


        if (Task_1ms_Flag) {
            Task_1ms();
            Task_1ms_Flag = 0;
        }

        if (Task_2ms_Flag) {
            Task_2ms();
            Task_2ms_Flag = 0;
        }

        if (Task_5ms_Flag) {
            Task_5ms();
            Task_5ms_Flag = 0;
        }

        if (Task_10ms_Flag) {
            Task_10ms();
            Task_10ms_Flag = 0;
        }

        if (Task_50ms_Flag) {
            Task_50ms();
            Task_50ms_Flag = 0;
        }

        
    }

}


static void Task_1ms(void)
{
    SendCP();
}

static void Task_2ms(void)
{
    // LED_Task();
}

static void Task_5ms(void)
{

}

static void Task_10ms(void)
{

}

uint8_t gu8_temp;
static void Task_50ms(void)
{
   static u16 i = 0;
   uint8_t Dat;
   i++;
   setPWMDutyCycle(g_u16duty);
   setPWMFrequency(g_u16frq);
   if(i == 50)
   {
        i = 0;
        FifoDataPop(&USART_RecStruct , &Dat);
        // gu8_temp = GetFifoNowDepth(USART_RecStruct);
        USART_SendByteData(Dat);
   }
}



