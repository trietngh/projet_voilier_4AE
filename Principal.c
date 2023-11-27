#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_Plateau.h"
#include "Driver_UART.h"
#include "Driver_RTC.h"
#include "Driver_Roulis.h"


int main(void){

	PLATEAU_Init();
	PLATEAU_Enable();
	

	RTC_Init();
	RTC_Enable();
	RTC_SetTime(1,18,9,22,15,10,17); // date, jour, mois, annee, heure, minute, seconde
	RTC_GetTime(); 
	
	ROULIS_Init();
	
	do
	{
		
	} while (1);
}
