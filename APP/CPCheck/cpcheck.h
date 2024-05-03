#ifndef _CPCHECK_H
#define _CPCHECK_H

#include "pwm.h"
void SendCP(void);
void PwmOn(void);
void Pwmoff(void);
static u8 Send8BytePwmData(u8 *PWMData);
#endif
