#ifndef MYADC_H
#define MYADC_H
#include "stm32f10x.h"
#include <stdbool.h>


void MyADC_Init(void);
int Conversion(void);
void Tension_ADC_Init(void);
bool Tension_ADC_ok(void);

#define TIM1_CC1 0x0<<17
#define TIM1_CC2 0x1<<17
#define TIM1_CC3 0x2<<17
#define TIM2_CC2 0x3<<17
#define TIM3_TRGO 0x4<<17
#define TIM4_CC4 0x5<<17
#define EXT1_TIM8_TRGO 0x6<<17
#define SWSTART 0x7<<17

#endif
