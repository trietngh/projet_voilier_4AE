/**
 * @file Driver_ADC.c
 * @author Louison TETAZ - Julie REVELLI
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "stm32f10x.h"
#include "Driver_Timer.h"
#include "Driver_GPIO.h"
#include "Driver_ADC.h"

void MyADC_Init(){
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	ADC1->CR2 |= ADC_CR2_ADON;
	
	ADC1->SQR1&= ~(ADC_SQR1_L);
	ADC1->SQR3|= 8;
	
	ADC1->CR2 |= ADC_CR2_EXTTRIG;
	ADC1->CR2 |= SWSTART;
	
	ADC1->CR2 |= ADC_CR2_CAL;
	while (ADC1->CR2 & ADC_CR2_CAL);
}

int Conversion(){


	ADC1->CR2 |= ADC_CR2_SWSTART;

	while(!(ADC1->SR & ADC_SR_EOC) ) {} // attente de la fin de conversion
  ADC1->SR &= ~ADC_SR_EOC; // validation de la conversion
  return ADC1->DR & ~((0x0F) << 12); // retour de la conversion
}

void Tension_ADC_Init(void){
	MyGPIO_Struct_TypeDef MaTenBat={GPIOB, 0, In_PullUp};
	//initialisation pin
	MyGPIO_Init(&MaTenBat);
	//init adc
	MyADC_Init();
}

bool Tension_ADC_ok(void){
	int ten = 0;
	ten = Conversion();
	
	if (ten < 1066)
	{
		return false;
		//afficher message tension trop faible
	}
	else
		return true;
}
