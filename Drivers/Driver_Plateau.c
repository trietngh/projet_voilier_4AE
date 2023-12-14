#include "stm32f10x.h"
#include "Driver_Plateau.h"

#define Plateau_PWM_GPIO GPIOA
#define Plateau_PWM_Pin 1

#define Plateau_DIR_GPIO GPIOA
#define Plateau_DIR_Pin 4

#define Plateau_Timer TIM2
#define Plateau_Timer_ARR 99
#define Plateau_Timer_PSC 35
#define Plateau_Timer_Channel 2

Plateau_Struct_Typedef MonPlateau_global;
MyGPIO_Struct_TypeDef Plateau_PWM = {Plateau_PWM_GPIO, Plateau_PWM_Pin, AltOut_Ppull};
MyGPIO_Struct_TypeDef Plateau_DIR = {Plateau_DIR_GPIO, Plateau_DIR_Pin, Out_Ppull};
MyTimer_Struct_TypeDef Plateau_Timer_pour_PWM = {Plateau_Timer, Plateau_Timer_ARR, Plateau_Timer_PSC};

void PLATEAU_Init (){
	MonPlateau_global.Channel_PWM = Plateau_Timer_Channel; 
	MonPlateau_global.DIR_Pin = &Plateau_DIR;
	MonPlateau_global.PWM_Pin = &Plateau_PWM;
	MonPlateau_global.Timer_Plateau = &Plateau_Timer_pour_PWM;
	
	//Init GPIO pour PWM et Direction de rotation du plateau
	MyGPIO_Init(MonPlateau_global.PWM_Pin);
	MyGPIO_Init(MonPlateau_global.DIR_Pin);
	
	//Init Timer pour PWM
	MyTimer_Base_Init(MonPlateau_global.Timer_Plateau);

	//Configurer le timer pour PWM
	MyTimer_PWM(MonPlateau_global.Timer_Plateau->Timer, MonPlateau_global.Channel_PWM);	
}


void PLATEAU_Enable (){	
	//Enable Timer pour PWM
	MyTimer_Base_Start(MonPlateau_global.Timer_Plateau->Timer);

}

//Callback function for receiving from USART
void PLATEAU_Receive_Cmd(void){
	
	char octet_received;
	unsigned short duty_cycle_PWM;
	
	octet_received = BUFFER[0];
	
	//Envoyer bit de direction
	if((octet_received & 0x80) == 0x80){
		MyGPIO_Set(MonPlateau_global.DIR_Pin->GPIO,MonPlateau_global.DIR_Pin->GPIO_Pin);
		octet_received = ~octet_received + 1;
	}
	else{
		MyGPIO_Reset(MonPlateau_global.DIR_Pin->GPIO,MonPlateau_global.DIR_Pin->GPIO_Pin);
	}
	
	
	//Convertir le duty_cycle
	duty_cycle_PWM = (unsigned short)octet_received;
	
	//Configurer le rapport cyclique de PWM
	MyTimer_PWM_DutyCycle(MonPlateau_global.Timer_Plateau, MonPlateau_global.Channel_PWM, duty_cycle_PWM);
}
