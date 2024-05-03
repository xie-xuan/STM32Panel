/*
 * @Author: xuanxie xiexuanlinux@126.com
 * @Date: 2024-03-06 02:50:24
 * @LastEditors: xuanxie xiexuanlinux@126.com
 * @LastEditTime: 2024-03-11 02:31:50
 * @FilePath: \PWM发波\APP\CPcheck.c
 * @Description: 
 * 
 * Copyright (c) 2024 by xiexuan , All Rights Reserved. 
 */
#include "cpcheck.h"

#define ReadyPhase          (1u)
#define StartPhase          (2u)
#define S2Onoff1Phase       (3u)
#define DataHeadPhase       (4u)
#define DataSendPhase       (5u)
#define DataEnd             (6u)


#define ReadyPhaseCnter          (300u)
#define StartPhaseCnter          (5u)
#define S2Onoff1PhaseCnter       (200u)
#define DataHeadPhaseCnter       (50u)
#define DataSendPhaseCnter       (10000u)
#define DataEndCnter             (500u)

u8 gu8_pwmTest = 0;
u8 gu8_pwmflag = ReadyPhase;
u8 PwmData[8] = {3,5,6,4,9,5,2,7};
u8  caseflg = ReadyPhase;
/// @brief 在1ms的Task里调用
/// @param  
void SendCP(void)
{

    
    static u16 Cnt = 0;


    switch(caseflg)
    {
        case (ReadyPhase):
        {
            if(Cnt < ReadyPhaseCnter)
            {
                Pwmoff();
                Cnt++;
            }
            else
            {
                Cnt = 0;
                caseflg = StartPhase;
            }
        }break;
        case (StartPhase):
        {
            if(Cnt < StartPhaseCnter)
            {
                PwmOn();
                Cnt++;
            }
            else
            {
                Cnt = 0;
                caseflg = S2Onoff1Phase;
            }
        }break;
        case (S2Onoff1Phase):
        {
            Pwmoff();
            caseflg = DataHeadPhase;
        }break;
        case (DataHeadPhase):
        {
            if(Cnt < DataHeadPhaseCnter)
            {
                Pwmoff();
                Cnt++;
            }
            else
            {
                Cnt = 0;
                caseflg = DataSendPhase;
            }
        }break;
        case (DataSendPhase): 
        {
            if(Send8BytePwmData(PwmData) == 0)
            {
                caseflg = DataEnd;
            }
        }break;
        case (DataEnd):break;

        default:break;
    }

}


void PwmOn(void)
{
    TIM_Cmd(TIM2,ENABLE);
    gu8_pwmTest = 1;
}

void Pwmoff(void)
{
    TIM_Cmd(TIM2,DISABLE);
    gu8_pwmTest = 0;
}


static u8 Send8BytePwmData(u8 *PWMData)
{
    static u8 i = 0,j = 0,k = 0;
    

    if(j < PwmData[i])
    {
        PwmOn();
        j++;
    }
    else
    {
        if(k < 20)
        {
            Pwmoff();
            k++;
        }
        else
        {
            i++;
            j = 0;
            k = 0;
        }

    }

    if(i < 8)
    {
        return 1;
    }
    else
    {
        i = 0;
        k = 0;
        j = 0;
        return 0;
    }
    

}
