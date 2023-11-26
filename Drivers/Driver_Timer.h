#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"

typedef struct
{
	TIM_TypeDef * Timer ; // TIM1 à TIM4
	unsigned short ARR ;
	unsigned short PSC ;
} MyTimer_Struct_TypeDef ;

void MyTimer_Base_Init (MyTimer_Struct_TypeDef * MyTimer) ;

void MyTimer_ActiveIT (TIM_TypeDef * Timer, char Prio, void (*IT_handler) (void));

void MyTimer_ChangeARR (MyTimer_Struct_TypeDef * MyTimer, unsigned short new_ARR);

void MyTimer_PWM(TIM_TypeDef * Timer, char Channel);

void MyTimer_PWM_DutyCycle(MyTimer_Struct_TypeDef * MyTimer, char Channel, unsigned short ratio);

void TIM1_UP_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);

#define MyTimer_Base_Start(Timer) (Timer)->CR1|= TIM_CR1_CEN;
#define MyTimer_Base_Stop(Timer) (Timer)->CR1&= ~TIM_CR1_CEN;
#endif
