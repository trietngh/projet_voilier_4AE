#include "stm32f10x.h"
#include "Driver_Telecommande.h"
#include "Driver_UART.h"
#include "Driver_Plateau.h"
#include "Driver_RTC.h"

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

void TELECOM_Send_Message(){
	char Time_To_Send[6];
	RTC_GetTime(); 
	Time_To_Send[0] = RTC_Current_Time.heure;
	Time_To_Send[1] = 'h';
	Time_To_Send[2] = RTC_Current_Time.minute;
	Time_To_Send[3] = 'm';
	Time_To_Send[4] = RTC_Current_Time.seconde;
	Time_To_Send[5] = 's';
	MyUART_Send(&Telecom_Struct_UART, Time_To_Send, 6);

}


