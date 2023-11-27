#ifndef DELAY_H
#define DELAY_H

#include "stm32f10x.h"
#include "Driver_Timer.h"

void DELAY_Init(void);

/* Provide a delay of time_delay ms */
void DELAY_WaitFor(unsigned short time_delay);

#endif
