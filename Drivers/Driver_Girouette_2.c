#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_ADC.h"
#include "Driver_Girouette.h"

void Girouette_Init(void)
{
	//initialisation des structures
	MyGPIO_Struct_TypeDef MonIndex ={GPIOB, 2, In_PullUp};
	MyTimer_Struct_TypeDef MonTIM = {TIM3, 0xFFFF, 0};
	
	//initialisation timer
	MyTimer_Base_Init(&MonTIM);
	
	//demarrer timer
	MyTimer_Base_Start(TIM3);
	
	//initialisation Index
	MyGPIO_Init(&MonIndex);
}

void Girouette ()
{
	//configuration deux voies
	TIM3->SMCR &= ~(TIM_SMCR_SMS);
	TIM3->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
	
	//configuration polarite non inversee
	//TIM3->CCER |= TIM_CCER_CC1P;
	//TIM3->CCER |= TIM_CCER_CC2P;
	// par defaut c'est à 0
	
	//configuration alignement des voies == TI1 sur TI1FP1 et pareil pour TI2
	TIM3->CCMR1 &= ~(TIM_CCMR1_CC1S);
	TIM3->CCMR1 |= TIM_CCMR1_CC1S_0;
	
	TIM3->CCMR1 &= ~(TIM_CCMR1_CC2S);
	TIM3->CCMR1 |= TIM_CCMR1_CC2S_0;
	
	
	
	TIM3->DIER |= TIM_DIER_UIE;
	NVIC->ISER[0] |= (1 << 8) ; // demande d'interruption
	NVIC->IP[8] = 1 << 4 ; // mettre la priorite sur l'interruption
	
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI2_PB;
	EXTI->RTSR |= EXTI_RTSR_TR2;
	EXTI->IMR |= EXTI_IMR_MR2;
	//EXTI->PR |= EXTI_PR_PR2;
}
