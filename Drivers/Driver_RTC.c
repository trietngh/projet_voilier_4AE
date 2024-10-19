/**
 * @file Driver_RTC.c
 * @author TANG Cam - NGUYEN Triet 
 * @date 2023-12-15
 * @copyright Copyright (c) 2023
 * 
 */
#include "stm32f10x.h"
#include "Driver_I2C.h"
#include "Driver_RTC.h"
#include "string.h"

Time_RTC_Typedef RTC_Current_Time;

void ITErr_function(){
}


void RTC_Init(){
	MyI2C_Init(RTC_I2C, RTC_IRQ_PRIORITE, &ITErr_function);
}


void RTC_SetTime(char Date ,char Jour, char Mois, char Annee, char Heure, char Min, char Sec){
	char TimeInfoToSend[RTC_TIME_MESSAGE_LENGTH];
	MyI2C_RecSendData_Typedef dataToSend;

	
	//Construire le msg à envoyer
	TimeInfoToSend[0] = (Sec % 10) + ((Sec/10) << 4);
	TimeInfoToSend[1] = (Min % 10) + ((Min/10) << 4);
	TimeInfoToSend[2] = (Heure % 10) + ((Heure/10) << 4) + (RTC_HEURE_MODE_24<<6);
	TimeInfoToSend[3] = Date;
	TimeInfoToSend[4] = (Jour % 10) + ((Jour/10) << 4);
	TimeInfoToSend[5] = (Mois % 10) + ((Mois/10) << 4);
	TimeInfoToSend[6] = (Annee % 10) + ((Annee/10) << 4);
	
	dataToSend.SlaveAdress7bits = RTC_ADRESSE;
	dataToSend.Ptr_Data = TimeInfoToSend;
	dataToSend.Nb_Data = RTC_TIME_MESSAGE_LENGTH;
	
	MyI2C_PutString(RTC_I2C, RTC_REGISTRE_DEBUT_ADRESSE, &dataToSend);

}

void RTC_Enable(){
	char msg = RTC_ENABLE_MSG;
	char longueur_msg = 1;
	
	MyI2C_RecSendData_Typedef dataToSend;
	dataToSend.SlaveAdress7bits = RTC_ADRESSE;
	dataToSend.Ptr_Data = &msg;
	dataToSend.Nb_Data = longueur_msg;
	MyI2C_PutString(RTC_I2C, RTC_REGISTRE_DEBUT_ADRESSE, &dataToSend);
}

void RTC_Disable(){
	char msg = RTC_DISABLE_MSG;
	char longueur_msg = 1;
	
	MyI2C_RecSendData_Typedef dataToSend;
	dataToSend.SlaveAdress7bits = RTC_ADRESSE;
	dataToSend.Ptr_Data = &msg;
	dataToSend.Nb_Data = longueur_msg;
	
	MyI2C_PutString(RTC_I2C, RTC_REGISTRE_DEBUT_ADRESSE, &dataToSend);
}

void RTC_GetTime(){
	char time_from_rtc[RTC_TIME_MESSAGE_LENGTH];
	
	MyI2C_RecSendData_Typedef dataToRec;
	dataToRec.SlaveAdress7bits = RTC_ADRESSE;
	dataToRec.Ptr_Data = time_from_rtc;
	dataToRec.Nb_Data = RTC_TIME_MESSAGE_LENGTH;
	
	MyI2C_GetString(RTC_I2C, RTC_REGISTRE_DEBUT_ADRESSE, &dataToRec);
	
	RTC_Current_Time.seconde = time_from_rtc[0] & MASK_GET_SECONDE;
	//RTC_Current_Time.seconde = (RTC_Current_Time.seconde & MASK_UNITAIRE) + ((RTC_Current_Time.seconde>>4)*10);
	
	RTC_Current_Time.minute = time_from_rtc[1];
	//RTC_Current_Time.minute = (RTC_Current_Time.minute & MASK_UNITAIRE) + ((RTC_Current_Time.minute>>4)*10);
	
	RTC_Current_Time.heure = time_from_rtc[2] & MASK_GET_HEURE;
	//RTC_Current_Time.heure = (RTC_Current_Time.heure & MASK_UNITAIRE) + ((RTC_Current_Time.heure>>4)*10);
	
	RTC_Current_Time.date = time_from_rtc[3];
	
	RTC_Current_Time.jour = time_from_rtc[4];
	//RTC_Current_Time.jour = (RTC_Current_Time.jour & MASK_UNITAIRE) + ((RTC_Current_Time.jour>>4)*10);
	
	RTC_Current_Time.mois = time_from_rtc[5];
	//RTC_Current_Time.mois = (RTC_Current_Time.mois & MASK_UNITAIRE) + ((RTC_Current_Time.mois>>4)*10);

	RTC_Current_Time.annee = time_from_rtc[6];
	//RTC_Current_Time.annee = (RTC_Current_Time.annee & MASK_UNITAIRE) + ((RTC_Current_Time.annee>>4)*10);

}
