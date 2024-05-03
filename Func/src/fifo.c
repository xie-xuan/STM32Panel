/*
 * @Author: xuanxie xiexuanlinux@126.com
 * @Date: 2024-04-23 01:16:42
 * @LastEditors: xuanxie xiexuanlinux@126.com
 * @LastEditTime: 2024-04-30 01:53:41
 * @FilePath: \综合平台\Func\src\fifo.c
 * @Description: 
 * 
 * Copyright (c) 2024 by xiexuan , All Rights Reserved. 
 */
#include "fifo.h"
#include "stdlib.h"
#include "string.h"

#ifndef GetFifoNowDepth
#define GetFifoNowDepth(FifoStruct)  \
        (FifoStruct->StartIndex >= FifoStruct->EndIndex)? \
        (FifoStruct->StartIndex - FifoStruct->EndIndex) :\
        (FifoStruct->StartIndex + (FifoStruct->MaxDepth - FifoStruct->EndIndex))
#endif



void FifoStructCreate(FifoStructTypeDef *FifoStruct , uint8_t MaxDepth)
{
    FifoStruct->MaxDepth = MaxDepth;
    FifoStruct->Data = (uint8_t*)malloc((FifoStruct->MaxDepth) * sizeof(uint8_t));
}

void FifoStructInit(FifoStructTypeDef *FifoStruct)
{
    FifoStruct->StartIndex = 0;
    FifoStruct->EndIndex = 0;

    memset(FifoStruct->Data,0,FifoStruct->MaxDepth);
}

uint8_t gu8_debugTemp;
FiFoStatus FifoDataPop(FifoStructTypeDef *FifoStruct , uint8_t *dat)
{
    uint8_t temp;
    temp =  GetFifoNowDepth(FifoStruct);
    if(temp == 0)
    {
        return -1; //深度为0，没有元素可以读出
    }
    
    *dat = FifoStruct->Data[FifoStruct->EndIndex];

    if(FifoStruct->EndIndex < FifoStruct->MaxDepth)
    {
        FifoStruct->EndIndex++; //在正半周期以内正常++
    }
    else
    {
        FifoStruct->EndIndex = 0; //超范围，换页
    }
    
    return 0; //读出成功

}

FiFoStatus FifoDataPush(FifoStructTypeDef *FifoStruct , uint8_t Dat)
{
    uint8_t temp;
    temp =  GetFifoNowDepth(FifoStruct);
    if(temp == FifoStruct->MaxDepth)
    {
        return -1; //达到最大深度，没有位置可以写入
    }

    FifoStruct->Data[FifoStruct->StartIndex] = Dat;

    if(FifoStruct->StartIndex < FifoStruct->MaxDepth)
    {
        FifoStruct->StartIndex++; //在正半周期以内正常++
    }
    else
    {
        FifoStruct->StartIndex = 0; //超范围，换页
    }
    return 0; //写入成功
}

// inline uint8_t GetFifoNowDepth(FifoStructTypeDef *FifoStruct)
// {
//     if(FifoStruct->StartIndex >= FifoStruct->EndIndex) 
//     {
//         return (FifoStruct->StartIndex - FifoStruct->EndIndex); //两个指针都在正半周期，返回(StartIndex - EndIndex)
//     }
//     else
//     {
//         return (FifoStruct->StartIndex + (FifoStruct->MaxDepth - FifoStruct->EndIndex)); //StartIndex 指针已经超过一圈了，深度为 正半(StartIndex - 0) + 负半(MaxDepth - EndIndex)
//     }
// }
