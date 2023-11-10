#ifndef MYUART_H
#define MYUART_H
#include "stm32f10x.h"
#include "Driver_GPIO.h"

#define BUFFER_SIZE 18

#define F_CLK 72000000

#define BAUD_9600 9600
#define BAUD_19200 19200
#define BAUD_38400 38400

#define STOP_BIT_1 0
#define STOP_BIT_05 1
#define STOP_BIT_2 2
#define STOP_BIT_15 3

#define WORD_LENGTH_8 8
#define WORD_LENGTH_9 9

#define WITH_PARITY 1
#define NO_PARITY 0

extern char BUFFER[BUFFER_SIZE];
extern uint8_t INDEXER_BUFFER;

typedef struct
{
	USART_TypeDef * UART ; // UART1 à UART3
	int TX_pin;
	int RX_pin;
	GPIO_TypeDef * GPIO ;

	
	uint16_t baud_rate;
	uint16_t stop_bit;
	uint16_t length_word;
	uint16_t parity;
	
} MyUART_Struct_TypeDef ;

void MyUART_Init(MyUART_Struct_TypeDef * MyUART);
void MyUART_Enable(MyUART_Struct_TypeDef * MyUART);
void MyUART_Send(MyUART_Struct_TypeDef * MyUART, char * msg, uint16_t size_of_msg);
void MyUART_Enable_Receive_IT(MyUART_Struct_TypeDef * MyUART, char Priorite, void (*IT_handler) (void));

void USART1_IRQHandler (void);
void USART2_IRQHandler (void);
void USART3_IRQHandler (void);

#endif
