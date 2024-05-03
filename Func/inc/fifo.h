/*
 * @Author: xuanxie xiexuanlinux@126.com
 * @Date: 2024-04-23 01:18:16
 * @LastEditors: xuanxie xiexuanlinux@126.com
 * @LastEditTime: 2024-04-30 01:53:58
 * @FilePath: \综合平台\Func\inc\fifo.h
 * @Description: 
 * 
 * Copyright (c) 2024 by xiexuan , All Rights Reserved. 
 */
#ifndef __FIFO_H
#define __FIFO_H
#include "stm32f10x.h"

typedef int8_t FiFoStatus;
/*
0   success
-1  fail
*/


typedef struct
{
    uint8_t StartIndex;
    uint8_t EndIndex;
    uint8_t MaxDepth;
    uint8_t *Data;
}FifoStructTypeDef;




void FifoStructCreate(FifoStructTypeDef *FifoStruct , uint8_t MaxDepth);
void FifoStructInit(FifoStructTypeDef *FifoStruct);
FiFoStatus FifoDataPop(FifoStructTypeDef *FifoStruct , uint8_t *dat);
FiFoStatus FifoDataPush(FifoStructTypeDef *FifoStruct , uint8_t Dat);
// uint8_t GetFifoNowDepth(FifoStructTypeDef *FifoStruct);

#endif

