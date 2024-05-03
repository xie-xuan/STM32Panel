/*
 * @Author: xuanxie xiexuanlinux@126.com
 * @Date: 2024-04-18 02:39:07
 * @LastEditors: xuanxie xiexuanlinux@126.com
 * @LastEditTime: 2024-04-29 02:08:26
 * @FilePath: \综合平台\BSP\inc\usart.h
 * @Description: 
 * 
 * Copyright (c) 2024 by xiexuan , All Rights Reserved. 
 */
#ifndef __usart_H
#define __usart_H

#include "stm32f10x.h"
#include "bit_band.h"
#include "stdio.h"
#include "fifo.h"

#define USARTBUADRATE   (9600)
extern FifoStructTypeDef USART_RecStruct;

int fputc(int ch,FILE *p);
void USART1_Init(void);
void USART_SendByteData(u8 data);
void USART_Main(void);

#endif


