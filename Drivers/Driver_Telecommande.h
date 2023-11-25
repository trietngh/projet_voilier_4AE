#ifndef MYTELECOM_H
#define MYTELECOM_H
#include "stm32f10x.h"

#define TELECOM_USART USART1
#define TELECOM_USART_TX 9
#define TELECOM_USART_RX 10
#define TELECOM_USART_GPIO GPIOA

void TELECOM_Init (void);
void TELECOM_Enable(void);
void TELECOM_Send_Message(void);


#endif
