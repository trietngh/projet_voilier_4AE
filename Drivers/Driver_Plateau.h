#ifndef PLATEAU_H
#define PLATEAU_H

#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "Driver_UART.h"
#include "Driver_Timer.h"

#define Plateau_PWM_GPIO GPIOB
#define Plateau_PWM_Pin 1

#define Plateau_DIR_GPIO GPIOA
#define Plateau_DIR_Pin 6

#define Plateau_Timer TIM3
#define Plateau_Timer_ARR 99
#define Plateau_Timer_PSC 35
#define Plateau_Timer_Channel 4

#define Plateau_USART USART1
#define Plateau_USART_TX 9
#define Plateau_USART_RX 10
#define Plateau_USART_GPIO GPIOA

//	Structure pour la configuration du STM32 pour utiliser le plateau.
typedef struct {
	MyUART_Struct_TypeDef * UART_Plateau ;
	MyTimer_Struct_TypeDef * Timer_Plateau;
	MyGPIO_Struct_TypeDef * PWM_Pin;
	MyGPIO_Struct_TypeDef * DIR_Pin;
	uint8_t Channel_PWM; 
	
} Plateau_Struct_Typedef;

void PLATEAU_Init(void);
void PLATEAU_Enable(void);



#endif
