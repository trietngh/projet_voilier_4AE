/**
 * @file Telecommande.c
 * @author TANG Cam - NGUYEN Triet 
 * @date 2023-12-15
 * @copyright Copyright (c) 2023
 * 
 */

#include "stm32f10x.h"
#include "Driver_Telecommande.h"
#include "Driver_UART.h"
#include "Driver_Plateau.h"
#include "Driver_RTC.h"

#define MASK_UNITAIRE	0x0F
#define MSG_LENGTH		10

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


void TELECOM_Send_Message(char * StringToSend, int length_string){
	char Time_To_Send[MSG_LENGTH];
	char end_line = '\n';
	RTC_GetTime(); 
	Time_To_Send[0] = (RTC_Current_Time.heure >> 4) + 0x30;
	Time_To_Send[1] = (RTC_Current_Time.heure & MASK_UNITAIRE) + 0x30;
	Time_To_Send[2] = 'h';
	Time_To_Send[3] = (RTC_Current_Time.minute >> 4) + 0x30;
	Time_To_Send[4] = (RTC_Current_Time.minute & MASK_UNITAIRE) + 0x30;
	Time_To_Send[5] = 'm';
	Time_To_Send[6] = (RTC_Current_Time.seconde >> 4) + 0x30;
	Time_To_Send[7] = (RTC_Current_Time.seconde & MASK_UNITAIRE) + 0x30;
	Time_To_Send[8] = 's';
	Time_To_Send[9] = ' ';
	
	MyUART_Send(&Telecom_Struct_UART, Time_To_Send, MSG_LENGTH);
	MyUART_Send(&Telecom_Struct_UART, StringToSend, length_string);
	MyUART_Send(&Telecom_Struct_UART, &end_line, 1);



}


