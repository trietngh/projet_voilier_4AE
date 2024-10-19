/**
 * @file Driver_Delay.h
 * @author TANG Cam - NGUYEN Triet 
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef DELAY_H
#define DELAY_H

#include "stm32f10x.h"
#include "Driver_Timer.h"

void DELAY_Init(void);

/* Provide a delay of time_delay ms */
void DELAY_WaitWithInterrupt(unsigned short time_delay_ms, void (* ptrFunctionWhileDelay)(void));
void DELAY_Wait(unsigned short time_delay_ms);

#endif
