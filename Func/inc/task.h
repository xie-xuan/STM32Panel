#ifndef __TASK_H
#define __TASK_H

#include "stm32f10x.h"
#include "Public.h"
#include "usart.h"
#include "fifo.h"

void Task(void);
static void Task_1ms(void);
static void Task_2ms(void);
static void Task_5ms(void);
static void Task_10ms(void);
static void Task_50ms(void);


#endif

