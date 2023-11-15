#include "stm32f10x.h"
#include "Driver_UART.h"
#include "Driver_GPIO.h"

char BUFFER[BUFFER_SIZE];
uint8_t INDEXER_BUFFER = 0;

void (*ptr_Fnc_Callback) (void);

void MyUART_Init(MyUART_Struct_TypeDef * MyUART){
	//Configuration pins pour Tx et Rx
	MyGPIO_Struct_TypeDef TX, RX;
	
	TX.GPIO = MyUART->GPIO; 
	TX.GPIO_Pin = MyUART->TX_pin; 
	TX.GPIO_Conf = AltOut_Ppull;
	
	RX.GPIO = MyUART->GPIO; 
	RX.GPIO_Pin = MyUART->RX_pin; 
	RX.GPIO_Conf = In_Floating;	
	
	// Init clock pour le UART
	if (MyUART->UART == USART1){
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	}
	else if (MyUART->UART == USART2){
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	}
	else if (MyUART->UART == USART3){
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	}
	
	// Mettre à jour BRR pour configurer baud rate
	// Formule: USART_DIV = F_CLK / (16*baud_rate)
	// BRR[15-4] = DIV_Mantissa = partie entière de USARTDIV
	// BRR[3-0] = DIV_Fraction = (partie décimale de USARTDIV * 16)
	if (MyUART->baud_rate == BAUD_9600){
		MyUART->UART->BRR &= 0xFFFF;
		MyUART->UART->BRR |= (F_CLK/(16*BAUD_9600) << 4) & 0xFFF0;
		MyUART->UART->BRR |= (F_CLK%(16*BAUD_9600)/BAUD_9600) & 0x000F;
	}
	else if (MyUART->baud_rate == BAUD_19200){
		MyUART->UART->BRR &= 0xFFFF;
		MyUART->UART->BRR |= (F_CLK/(16*BAUD_19200) << 4) & 0xFFF0;
		MyUART->UART->BRR |= (F_CLK%(16*BAUD_19200)/BAUD_19200) & 0x000F;
	}
	else if (MyUART->baud_rate == BAUD_38400){
		MyUART->UART->BRR &= 0xFFFF;
		MyUART->UART->BRR |= (F_CLK/(16*BAUD_38400) << 4) & 0xFFF0;
		MyUART->UART->BRR |= (F_CLK%(16*BAUD_38400)/BAUD_38400) & 0x000F;
	}

	//M = 0 : 8 data bits
	//M = 1 : 9 data bits
	if(MyUART->length_word == 9){
		MyUART->UART->CR1 |= USART_CR1_M;
	}
	else if(MyUART->length_word == 8){
		MyUART->UART->CR1 &= ~USART_CR1_M;
	}

	// stop bit = 0 : bits stop du CR2 = 00 : 1 stop bits
	// stop bit = 1 : bits stop du CR2 = 01 : 0.5 stop bits
	// stop bit = 2 : bits stop du CR2 = 10 : 2 stop bits
	// stop bit = 3 : bits stop du CR2 = 11 : 1.5 stop bits

	if(MyUART->stop_bit==0){
		MyUART->UART->CR2 &= ~USART_CR2_STOP;
	}
	else if(MyUART->stop_bit==1){
		MyUART->UART->CR2 &= ~USART_CR2_STOP;
		MyUART->UART->CR2 |= USART_CR2_STOP_0;
	}
	else if(MyUART->stop_bit==2){
		MyUART->UART->CR2 &= ~USART_CR2_STOP;
		MyUART->UART->CR2 |= USART_CR2_STOP_1;
	}
	else if(MyUART->stop_bit==3){
		MyUART->UART->CR2 |= USART_CR2_STOP;
	}
	
	// parite = 0 => pas de vérification de parité
	// parite = 1 => vérification de parité
	
	if(MyUART->parity == 1){
		// enable check parity on received data
		MyUART->UART->CR1 |= USART_CR1_PCE;
		// select even parity 
		MyUART->UART->CR1 &= ~USART_CR1_PS;
	}
	
	//Init AFIO pins pour Tx et Rx
	MyGPIO_Init(&TX);
	MyGPIO_Init(&RX);
}


void MyUART_Enable(MyUART_Struct_TypeDef * MyUART){
	// UART enable
	MyUART->UART->CR1 |= USART_CR1_UE;
	
	// enable transmitter et receiver
	MyUART->UART->CR1 |= USART_CR1_TE;
	MyUART->UART->CR1 |= USART_CR1_RE;
}

void MyUART_Send(MyUART_Struct_TypeDef * MyUART, char * msg, uint16_t number_of_char){
	int i;
	int length_of_word_send;
	int mask_bit;
	int length_data = number_of_char*8; // en bit
	
	// vevifier si utilisateur choisit check parity or not
	if(MyUART->parity == 1){
		length_of_word_send = MyUART->length_word - 1; // en bit
	}
	else if(MyUART->parity == 0){
		length_of_word_send = MyUART->length_word; // en bit
	}
	
	
	//definir les bits de masque selon la taille de data
	if(length_of_word_send == 8){
		mask_bit = 0xFF;
	}
	else if(length_of_word_send == 7){
		mask_bit = 0xEF;
	}
	else if(length_of_word_send == 9){
		mask_bit = 0x1FF;
	}
	
	//Note : on ne traite que le cas où length_of_word_send == 8 et parity == 0
	for (i=length_of_word_send; i <= length_data; i+= length_of_word_send) {
		
		while((MyUART->UART->SR & USART_SR_TXE) == 0){
		}
		MyUART->UART->DR &= ~(mask_bit);
		MyUART->UART->DR |= mask_bit & *msg;
		msg++;

	}
}

void MyUART_Enable_Receive_IT(MyUART_Struct_TypeDef * MyUART, char Priorite, void (*IT_handler) (void)){
	//Enable interruption for RXNE flag
	MyUART->UART->CR1 |= USART_CR1_RXNEIE;
	//Initialize indexer of buffer
	INDEXER_BUFFER = 0;
	ptr_Fnc_Callback = IT_handler;
	
	if (MyUART->UART == USART1){
		NVIC_EnableIRQ(USART1_IRQn);
		NVIC_SetPriority(USART1_IRQn, Priorite);
	}
	else if (MyUART->UART == USART2) {
		NVIC_EnableIRQ(USART2_IRQn);
		NVIC_SetPriority(USART2_IRQn, Priorite);
	}
	else if (MyUART->UART == USART3) {
		NVIC_EnableIRQ(USART3_IRQn);
		NVIC_SetPriority(USART3_IRQn, Priorite);
	}
}

void USART1_IRQHandler (){
	char data_receive;
	//Clear interrupt flag
	USART1->SR &= ~USART_SR_RXNE;
	//Write Data Registre to Buffer
	data_receive = (USART1->DR) & 0xFF;
	BUFFER[INDEXER_BUFFER] = data_receive;
	INDEXER_BUFFER++;
	if ((data_receive == 0x0D) || (INDEXER_BUFFER == BUFFER_SIZE)){
		if (ptr_Fnc_Callback != 0){
			INDEXER_BUFFER = 0;
			(*ptr_Fnc_Callback) ();
			
		}
	}
}

void USART2_IRQHandler (){
	char data_receive;
	//Clear interrupt flag
	USART2->SR &= ~USART_SR_RXNE;
	//Write Data Registre to Buffer
	data_receive = (USART1->DR) & 0xFF;
	BUFFER[INDEXER_BUFFER] = data_receive;
	INDEXER_BUFFER++;
	if ((data_receive == 0x0D) || (INDEXER_BUFFER == BUFFER_SIZE)){
		if (ptr_Fnc_Callback != 0){
			INDEXER_BUFFER = 0;
			(*ptr_Fnc_Callback) ();
		}
	}
}

void USART3_IRQHandler (){
	char data_receive;
	//Clear interrupt flag
	USART3->SR &= ~USART_SR_RXNE;
	//Write Data Registre to Buffer
	data_receive = (USART1->DR) & 0xFF;
	BUFFER[INDEXER_BUFFER] = data_receive;
	INDEXER_BUFFER++;
	if ((data_receive == 0x0D) || (INDEXER_BUFFER == BUFFER_SIZE)){
		if (ptr_Fnc_Callback != 0){
			INDEXER_BUFFER = 0;
			(*ptr_Fnc_Callback) ();
		}
	}
}
