/**
 * @file Driver_Timer.c
 * @author TANG Cam - NGUYEN Triet 
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "stm32f10x.h"
#include "Driver_Timer.h"

void (*ptr_Fnc_Handler) (void);

void MyTimer_Base_Init (MyTimer_Struct_TypeDef * MyTimer){
	
	// Init clock pour le timer
	if (MyTimer->Timer == TIM1){
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	}
	else if (MyTimer->Timer == TIM2){
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	}
	else if (MyTimer->Timer == TIM3){
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	}
	else if (MyTimer->Timer == TIM4){
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	}
	
	// Configurer Prescaler
	MyTimer->Timer->PSC = MyTimer->PSC;
	
	//Configurer Autoreload Register
	MyTimer->Timer->ARR = MyTimer->ARR;
	
}


void MyTimer_ActiveIT (TIM_TypeDef * Timer, char Prio, void (*IT_handler) (void)){
	//Mettre à 1 le registre UIE
	//Permettre l'événement à propager vers NVIC
	Timer->DIER |= TIM_DIER_UIE;
	
	// Activer l'interruption pour le Timer
	if (Timer == TIM1){
		NVIC_EnableIRQ(TIM1_UP_IRQn);
		NVIC_SetPriority(TIM1_UP_IRQn, Prio);
	}
	else if (Timer == TIM2){
		NVIC_EnableIRQ(TIM2_IRQn);
		NVIC_SetPriority(TIM2_IRQn, Prio);
	}
	else if (Timer == TIM3){
		NVIC_EnableIRQ(TIM3_IRQn);
		NVIC_SetPriority(TIM3_IRQn, Prio);
	}
	else if (Timer == TIM4){
		NVIC_EnableIRQ(TIM4_IRQn);
		NVIC_SetPriority(TIM4_IRQn, Prio);
	}
	
	ptr_Fnc_Handler = IT_handler;
}



void MyTimer_ChangeARR (MyTimer_Struct_TypeDef * MyTimer, unsigned short new_ARR) {
	//Reconfigurer Autoreload Register
	MyTimer->Timer->ARR = new_ARR;
}

void MyTimer_ResetCNT (MyTimer_Struct_TypeDef * MyTimer){
	MyTimer->Timer->CNT = 0x00;
}

void MyTimer_PWM(TIM_TypeDef * Timer, char Channel){
	//configurer le timer pour PWM
	//Set the auto-reload preload register
		Timer->CR1 |= TIM_CR1_ARPE;
		
		//Set to edge-aligned mode
		Timer->CR1 &= ~TIM_CR1_CMS;	//2bits CMS = 00
		
		//Set to upcounting
		Timer->CR1 &= ~TIM_CR1_DIR;
		
		//Initialize all registre
		Timer->EGR |= TIM_EGR_UG;
	
	if (Timer == TIM1){
		Timer->BDTR |= TIM_BDTR_MOE;
	}
	
	if (Channel==1){
		//Configure to PWM mode
		Timer->CCMR1 &= ~TIM_CCMR1_OC1M;
		Timer->CCMR1 |= TIM_CCMR1_OC1M_2 + TIM_CCMR1_OC1M_1;
		//Enable preload register
		Timer->CCMR1 |= TIM_CCMR1_OC1PE;
		
		//Configure the polarisation
		Timer->CCER |= TIM_CCER_CC1E;
		Timer->CCER &= ~TIM_CCER_CC1P;
	}
	else if (Channel == 2){
		//Configure to PWM mode
		Timer->CCMR1 &= ~TIM_CCMR1_OC2M;
		Timer->CCMR1 |= TIM_CCMR1_OC2M_2 + TIM_CCMR1_OC2M_1;
		//Enable preload register
		Timer->CCMR1 |= TIM_CCMR1_OC2PE;
		
		//Configure the polarisation
		Timer->CCER |= TIM_CCER_CC2E;
		Timer->CCER &= ~TIM_CCER_CC2P;
	}
	else if (Channel == 3) {
		//Configure to PWM mode
		Timer->CCMR2 &= ~TIM_CCMR2_OC3M;
		Timer->CCMR2 |= TIM_CCMR2_OC3M_2 + TIM_CCMR2_OC3M_1;
		//Enable preload register
		Timer->CCMR2 |= TIM_CCMR2_OC3PE;
		
		//Configure the polarisation
		Timer->CCER |= TIM_CCER_CC3E;
		Timer->CCER &= ~TIM_CCER_CC3P;
	}
	else if (Channel == 4) {
		//Configure to PWM mode
		Timer->CCMR2 &= ~TIM_CCMR2_OC4M;
		Timer->CCMR2 |= TIM_CCMR2_OC4M_2 + TIM_CCMR2_OC4M_1;
		//Enable preload register
		Timer->CCMR2 |= TIM_CCMR2_OC4PE;
		
		//Configure the polarisation
		Timer->CCER |= TIM_CCER_CC4E;
		Timer->CCER &= ~TIM_CCER_CC4P;
	}
}

void MyTimer_PWM_DutyCycle(MyTimer_Struct_TypeDef * MyTimer, char Channel, float ratio){
	if (Channel==1){
		MyTimer->Timer->CCR1 &= 0x0;
		MyTimer->Timer->CCR1 |= (uint16_t)((MyTimer->ARR+1)*ratio/100);
	}
	else if (Channel == 2){
		MyTimer->Timer->CCR2 &= 0x0;
		MyTimer->Timer->CCR2 |= (uint16_t)((MyTimer->ARR+1)*ratio/100);
	}
	else if (Channel == 3){
		MyTimer->Timer->CCR3 &= 0x0;
		MyTimer->Timer->CCR3 |= (uint16_t)((MyTimer->ARR+1)*ratio/100);
	}
	else if (Channel == 4){
		MyTimer->Timer->CCR4 &= 0x0;
		MyTimer->Timer->CCR4 |= (uint16_t)((MyTimer->ARR+1)*ratio/100);
	}
	
}

//Handler for update event of timer
void TIM1_UP_IRQHandler(){
	TIM1->SR &= ~(TIM_SR_UIF);
	if (ptr_Fnc_Handler != 0){
		(*ptr_Fnc_Handler) ();
	}
}

void TIM2_IRQHandler(){
	TIM2->SR &= ~(TIM_SR_UIF);
	if (ptr_Fnc_Handler != 0){
		(*ptr_Fnc_Handler) ();
	}
}

void TIM3_IRQHandler(){
	TIM3->SR &= ~(TIM_SR_UIF);
	if (ptr_Fnc_Handler != 0){
		(*ptr_Fnc_Handler) ();
	}
}

void TIM4_IRQHandler(){
	TIM4->SR &= ~(TIM_SR_UIF);
	if (ptr_Fnc_Handler != 0){
		(*ptr_Fnc_Handler) ();
	}
}


