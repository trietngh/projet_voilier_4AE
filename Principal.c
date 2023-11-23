#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_Plateau.h"
#include "Driver_UART.h"
#include "Driver_RTC.h"

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

int main(void){
//	Plateau_Struct_Typedef Plateau;
//	MyGPIO_Struct_TypeDef Plateau_PWM = {Plateau_PWM_GPIO, Plateau_PWM_Pin, AltOut_Ppull};
//	MyGPIO_Struct_TypeDef Plateau_DIR = {Plateau_DIR_GPIO, Plateau_DIR_Pin, Out_Ppull};
//	MyTimer_Struct_TypeDef Plateau_Timer_pour_PWM = {Plateau_Timer, Plateau_Timer_ARR, Plateau_Timer_PSC};
//	MyUART_Struct_TypeDef Plateau_UART = {Plateau_USART, Plateau_USART_TX, Plateau_USART_RX, Plateau_USART_GPIO, BAUD_9600, STOP_BIT_1, WORD_LENGTH_8, NO_PARITY};

//	Plateau.Channel_PWM = Plateau_Timer_Channel; 
//	Plateau.DIR_Pin = &Plateau_DIR;
//	Plateau.PWM_Pin = &Plateau_PWM;
//	Plateau.Timer_Plateau = &Plateau_Timer_pour_PWM;
//	Plateau.UART_Plateau = &Plateau_UART;
//	
//	PLATEAU_Init(&Plateau);
//	PLATEAU_Enable(&Plateau);
	

	RTC_Init();
	RTC_Enable();
	RTC_SetTime(1,18,9,22,15,10,17); // date, jour, mois, annee, heure, minute, seconde
	RTC_GetTime(); 
	do
	{
		
	} while (1);
}
