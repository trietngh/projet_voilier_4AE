/**
 * @file Plateau.h
 * @author TANG Cam - NGUYEN Triet 
 * @date 2023-12-15
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef PLATEAU_H
#define PLATEAU_H

#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "Driver_UART.h"
#include "Driver_Timer.h"

//	Structure pour la configuration du STM32 pour utiliser le plateau.
typedef struct {
	MyGPIO_Struct_TypeDef * PWM_Pin;
	MyTimer_Struct_TypeDef * Timer_Plateau;
	MyGPIO_Struct_TypeDef * DIR_Pin;
	uint8_t Channel_PWM; 
} Plateau_Struct_Typedef;

void PLATEAU_Init(void);
void PLATEAU_Enable(void);
void PLATEAU_Receive_Cmd(void);


#endif
