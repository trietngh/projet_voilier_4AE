#include "Driver_Delay.h"
#include <stdbool.h>

#define DELAY_Timer TIM4
#define DELAY_PSC	7199
#define DELAY_ARR 1

#define DELAY_IRQ_PRIO 3


MyTimer_Struct_TypeDef Timer_pour_Delay = {DELAY_Timer, DELAY_ARR, DELAY_PSC};
bool DELAY_CONTINUE = false;

void DELAY_IT_Handler(void){
	DELAY_CONTINUE = false;
}

void DELAY_Init(){
	MyTimer_Base_Init(&Timer_pour_Delay);
	MyTimer_ActiveIT (Timer_pour_Delay.Timer, DELAY_IRQ_PRIO, DELAY_IT_Handler);
}

void DELAY_WaitFor(unsigned short time_delay){
	unsigned short nouveau_ARR = time_delay*10 - 1;
	MyTimer_ChangeARR(&Timer_pour_Delay, nouveau_ARR);
	Timer_pour_Delay.ARR = nouveau_ARR;
	MyTimer_Base_Start(Timer_pour_Delay.Timer);
	DELAY_CONTINUE = true;
	while (DELAY_CONTINUE){
	
	}
	MyTimer_Base_Stop(Timer_pour_Delay.Timer);
	MyTimer_ResetCNT(&Timer_pour_Delay);
};
