#ifndef _PWM_H
#define _PWM_H

#include "bit_band.h"
#include "SysTick.h"

void setPWMFrequency(uint32_t frequency);
void setPWMDutyCycle(uint8_t dutyCycle);
void setGPIO_Init(void);
void TIM1_PWM_Init(uint32_t frequency, uint8_t dutyCycle);
#endif
