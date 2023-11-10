#ifndef PLATEAU_H
#define PLATEAU_H

#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "Driver_UART.h"
#include "Driver_Timer.h"

//	Structure pour la configuration du STM32 pour utiliser le plateau.
typedef struct {
	MyUART_Struct_TypeDef * UART_Plateau ;
	MyTimer_Struct_TypeDef * Timer_Plateau;
	MyGPIO_Struct_TypeDef * PWM_Pin;
	MyGPIO_Struct_TypeDef * DIR_Pin;
	uint8_t Channel_PWM; 
	
} Plateau_Struct_Typedef;

void PLATEAU_Init (Plateau_Struct_Typedef * MonPlateau);
void PLATEAU_Enable (Plateau_Struct_Typedef * MonPlateau);



#endif
