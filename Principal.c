#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_Plateau.h"
#include "Driver_UART.h"
#include "Driver_RTC.h"
#include "Driver_Telecommande.h"
#include "Driver_Delay.h"
#include "Driver_Roulis.h"


void Checking_Emergency (void){
	if ( ROULIS_CheckTiltLimit()){
		TELECOM_Send_Message("Deborde",7);
	}
}

int main(void){

	PLATEAU_Init();
	PLATEAU_Enable();
	
	
	TELECOM_Init();
	TELECOM_Enable();
	
	DELAY_Init();
	
	RTC_Init();
	RTC_Enable();
	RTC_SetTime(1,18,9,22,11,44,50); // date, jour, mois, annee, heure, minute, seconde

	
	
	ROULIS_Init();
	
	do
	{
		TELECOM_Send_Message("message en plus",15);

		DELAY_WaitWithInterrupt(3000, Checking_Emergency);
	} while (1);
}
