/**
 * @file Driver_GPIO.c
 * @author TANG Cam - NGUYEN Triet 
 * @date 2023-12-15
 * @copyright Copyright (c) 2023
 * 
 */

#include "stm32f10x.h"
#include "Driver_GPIO.h"

void MyGPIO_Init(MyGPIO_Struct_TypeDef * GPIOStructPtr){
	
	// Init clock
	if (GPIOStructPtr->GPIO == GPIOA){
		//GPIOA
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	}
	else if (GPIOStructPtr->GPIO == GPIOB){
		//GPIOB
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	}
	else if (GPIOStructPtr->GPIO == GPIOC){
		//GPIOC
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	}
	else if (GPIOStructPtr->GPIO == GPIOD){
		//GPIOD
		RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	}
	
	// config de Pull Up/Down dans ODR
	if (GPIOStructPtr->GPIO_Conf == In_PullDown){
		GPIOStructPtr->GPIO->ODR &=  ~(0x1 << GPIOStructPtr->GPIO_Pin);
	}
	if (GPIOStructPtr->GPIO_Conf == In_PullUp){
		GPIOStructPtr->GPIO->ODR |= 0x1 << GPIOStructPtr->GPIO_Pin;
	}
	
	// reprendre la bonne valeur config de Pull Up après distincguer avec le Pull down
	if (GPIOStructPtr->GPIO_Conf == In_PullUp){
		GPIOStructPtr->GPIO_Conf = GPIOStructPtr->GPIO_Conf - 1;
	}
	
	
	// config dans CRH / CRL
	if ((GPIOStructPtr->GPIO_Pin >= 0) && (GPIOStructPtr->GPIO_Pin <= 7)){
		GPIOStructPtr->GPIO->CRL &= ~(0xF << (GPIOStructPtr->GPIO_Pin*4));
		GPIOStructPtr->GPIO->CRL |= GPIOStructPtr->GPIO_Conf << (GPIOStructPtr->GPIO_Pin*4);
	}
	else if ((GPIOStructPtr->GPIO_Pin >= 8) && (GPIOStructPtr->GPIO_Pin <= 15)){
		GPIOStructPtr->GPIO->CRH &= ~(0xF << ((GPIOStructPtr->GPIO_Pin - 8)*4));
		GPIOStructPtr->GPIO->CRH |= GPIOStructPtr->GPIO_Conf << ((GPIOStructPtr->GPIO_Pin - 8)*4);
	}
	
}



int MyGPIO_Read (GPIO_TypeDef * GPIO , int GPIO_Pin){
	return (GPIO->IDR & (0x1 << GPIO_Pin)) >> GPIO_Pin;
}  // renvoie 0 ou autre chose different de 0

void MyGPIO_Set (GPIO_TypeDef * GPIO , int GPIO_Pin ){
	GPIO->BSRR |= 0x1 << GPIO_Pin;
}  
void MyGPIO_Reset (GPIO_TypeDef * GPIO , int GPIO_Pin ){
	GPIO->BSRR |= 0x1 << (GPIO_Pin + 16);
} 

void MyGPIO_Toggle (GPIO_TypeDef * GPIO , int GPIO_Pin ){
	GPIO->ODR = GPIO->ODR ^ (0x1 << GPIO_Pin);
}
