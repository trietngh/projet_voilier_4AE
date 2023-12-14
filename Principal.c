#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_Plateau.h"
#include "Driver_UART.h"
#include "Driver_RTC.h"
#include "Driver_Telecommande.h"
#include "Driver_Delay.h"
#include "Driver_Roulis.h"
#include "Driver_Girouette.h"
#include "Driver_ServoMoteur.h"
#include "Driver_ADC.h"
#include <stdbool.h>



	short angle_courant;

void Checking_Emergency (void){
	if (ROULIS_CheckTiltLimit()){
		TELECOM_Send_Message("Deborde",7);
		ServoMoteur(180);
		TELECOM_Send_Message("Regle",7);
	}
	else if (Tension_ADC_ok() == false){
		TELECOM_Send_Message("Battery low",11);
	}
	else{
		ServoMoteur(Girouette_GetAngle());
	}
}

int main(void){

	Tension_ADC_Init();

	PLATEAU_Init();
	PLATEAU_Enable();
	
	
	TELECOM_Init();
	TELECOM_Enable();
	
	Girouette_Init();
	Girouette();
	
	ServoMoteur_Init();
	
	DELAY_Init();
	
	RTC_Init();
	RTC_Enable();
	RTC_SetTime(1,18,9,22,11,44,50); // date, jour, mois, annee, heure, minute, seconde

	
	
  ROULIS_Init();
	
	
	do
	{
		angle_courant = Girouette_GetAngle();
		
		if( (0 <= angle_courant && angle_courant < 40) ||  (320 <= angle_courant && angle_courant < 360))
		{
			TELECOM_Send_Message("le voilier navigue au debout",28);
		}
		else if( (40 <= angle_courant && angle_courant < 50) ||  (310 <= angle_courant && angle_courant < 320))
		{
			TELECOM_Send_Message("le voilier navigue au pres",26);
		}
		else if( (50 <= angle_courant && angle_courant < 65) ||  (295 <= angle_courant && angle_courant < 310))
		{	
			TELECOM_Send_Message("le voilier navigue au bon plein",31);
		}
		else if((65 <= angle_courant && angle_courant < 115) ||  (245 <= angle_courant && angle_courant < 295) ){
			TELECOM_Send_Message("le voilier navigue au travers",29);
		}
		else if((115 <= angle_courant && angle_courant < 155) ||  (205 <= angle_courant && angle_courant < 245)){
			TELECOM_Send_Message("le voilier navigue au grand largue",34);
		}	
		else if(155 <= angle_courant && angle_courant < 205){
			TELECOM_Send_Message("le voilier navigue en arriere",29);
		}
		
		DELAY_WaitWithInterrupt(3000, Checking_Emergency);
	} while (1);
}
