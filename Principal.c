#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_Plateau.h"
#include "Driver_UART.h"
#include "Driver_RTC.h"
#include "Driver_Telecommande.h"
#include "Driver_Delay.h"
#include "Driver_Roulis.h"


int main(void){

	PLATEAU_Init();
	PLATEAU_Enable();
	
	
	TELECOM_Init();
	TELECOM_Enable();
	
	DELAY_Init();
	
	//RTC_Init();
	//RTC_Enable();
	//RTC_SetTime(1,18,9,22,11,44,50); // date, jour, mois, annee, heure, minute, seconde

	
	
	ROULIS_Init();
	
	do
	{
		if (ROULIS_CheckTiltLimit()){
			TELECOM_Send_Message('1');
		}
		else{
			TELECOM_Send_Message('0');
		}
		DELAY_WaitFor(1000);
	} while (1);
}
