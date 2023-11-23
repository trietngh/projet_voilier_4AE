#include "stm32f10x.h"
#include "Driver_Telecommande.h"
#include "Driver_UART.h"
#include "Driver_Plateau.h"

MyUART_Struct_TypeDef Telecom_Struct_UART = {TELECOM_USART, TELECOM_USART_TX, TELECOM_USART_RX, TELECOM_USART_GPIO, BAUD_9600, STOP_BIT_1, WORD_LENGTH_8, NO_PARITY};

void TELECOM_Init (){
	MyUART_Init(&Telecom_Struct_UART);
	
	//Enable interuption Receive UART
	MyUART_Enable_Receive_IT(&Telecom_Struct_UART, 0, PLATEAU_Receive_Cmd);
}

void TELECOM_Enable (){
	//Enable UART
	MyUART_Enable(&Telecom_Struct_UART);
}
