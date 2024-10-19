/**
 * @file Principal.c
 * @author TANG Cam - NGUYEN Triet - Louison TETAZ - Julie REVELLI
 * @brief Header de la fonction Main du projet Voilier - INSA Toulouse - 4AESE - TP2
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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


//variable global de l'angle courant de girouette 
short angle_courant;

//fonction de verifier les situations en urgence
void Checking_Emergency (void){
	if (ROULIS_CheckTiltLimit()){
		TELECOM_Send_Message("Deborde",7);
		ServoMoteur_Move(180);
	}
	else if (Tension_ADC_ok() == false){
		TELECOM_Send_Message("Battery low",11);
	}
	else{
		ServoMoteur_Move(Girouette_GetAngle());
	}
}

int main(void){

	//initialiser le niveau de tension
	Tension_ADC_Init();

	//initialiser et demarrer le plateau
	PLATEAU_Init();
	PLATEAU_Enable();
	
	//initialiser et demarrer la telecommande
	TELECOM_Init();
	TELECOM_Enable();
	
	//initialiser et demarrer la girouette
	Girouette_Init();
	Girouette_Conf();
	
	//initialiser servomoteur
	ServoMoteur_Init();
	
	//initialiser le timer pour le delais 3 secondes
	DELAY_Init();
	
	//initialiser et demarrer et set time pour Real Time Clock
	RTC_Init();
	RTC_Enable();
	RTC_SetTime(6,15,12,23,14,30,00); // date, jour, mois, annee, heure, minute, seconde

	//initialiser le roulis
  ROULIS_Init();
	
	
	do
	{
		//prendre l'angle de girouette courant
		angle_courant = Girouette_GetAngle();
		
		//afficher les messages selon la position de voilier chaque 3 secondes
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
		
		//toujours verifier les alerts 
		DELAY_WaitWithInterrupt(3000, Checking_Emergency);
	} while (1);
}
