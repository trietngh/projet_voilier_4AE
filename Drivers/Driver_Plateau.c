#include "stm32f10x.h"
#include "Driver_UART.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_Plateau.h"

Plateau_Struct_Typedef * MonPlateau_global;

//Callback function for receiving from USART
void USART_IT(void){
	
	char octet_received;
	unsigned short duty_cycle_PWM;
	
	octet_received = BUFFER[0];
	
	//Envoyer bit de direction
	if((octet_received & 0x80) == 0x80){
		MyGPIO_Set(MonPlateau_global->DIR_Pin->GPIO,MonPlateau_global->DIR_Pin->GPIO_Pin);
		octet_received = ~octet_received + 1;
	}
	else{
		MyGPIO_Reset(MonPlateau_global->DIR_Pin->GPIO,MonPlateau_global->DIR_Pin->GPIO_Pin);
	}
	
	
	//Convertir le duty_cycle
	duty_cycle_PWM = (unsigned short)octet_received;
	
	//Configurer le rapport cyclique de PWM
	MyTimer_PWM_DutyCycle(MonPlateau_global->Timer_Plateau, MonPlateau_global->Channel_PWM, duty_cycle_PWM);

	//Demarer le timer pour sortir PWM
	//MyTimer_Base_Start(MonPlateau_global->Timer_Plateau->Timer);
}

void PLATEAU_Init (Plateau_Struct_Typedef * MonPlateau){
	
	//Init GPIO pour PWM et Direction de rotation du plateau
	MyGPIO_Init(MonPlateau->PWM_Pin);
	MyGPIO_Init(MonPlateau->DIR_Pin);
	
	//Init Timer pour PWM
	MyTimer_Base_Init(MonPlateau->Timer_Plateau);

	//Configurer le timer pour PWM
	MyTimer_PWM(MonPlateau->Timer_Plateau->Timer, MonPlateau->Channel_PWM);
	
	//Init UART
	MyUART_Init(MonPlateau->UART_Plateau);
	
}


void PLATEAU_Enable (Plateau_Struct_Typedef * MonPlateau){
		
	//Enable interuption Receive UART
	MyUART_Enable_Receive_IT(MonPlateau->UART_Plateau, 0, USART_IT);

	//Monplateau global
	MonPlateau_global = MonPlateau;
	
	//Enable UART
	MyUART_Enable(MonPlateau->UART_Plateau);
	
	//Enable Timer pour PWM
	MyTimer_Base_Start(MonPlateau_global->Timer_Plateau->Timer);

}

