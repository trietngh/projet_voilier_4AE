#ifndef MYRTC_H
#define MYRTC_H

#include "stm32f10x.h"
#include "Driver_I2C.h"

#define RTC_I2C	I2C2

#define RTC_ADRESSE 0x68 
#define RTC_IRQ_PRIORITE 1
#define RTC_HEURE_MODE_24 0
#define RTC_REGISTRE_DEBUT_ADRESSE 0x0

#define RTC_TIME_MESSAGE_LENGTH 7
#define RTC_ENABLE_MSG 0x0
#define RTC_DISABLE_MSG 0x80
#define RTC_ERROR_MSG "9999999"

#define DIM 1
#define LUN 2
#define MAR 3
#define MER 4
#define JEU 5
#define VEN 6
#define SAM 7


#define MASK_GET_SECONDE 0x7F
#define MASK_GET_HEURE 0x3F
#define MASK_UNITAIRE 0x0F

typedef struct
{
	char seconde;
	char minute;
	char heure;
	char date;
	char jour;
	char mois;
	char annee;
} Time_RTC_Typedef;

extern Time_RTC_Typedef RTC_Current_Time;

void RTC_Init(void);
void RTC_SetTime(char Date, char Jour, char Mois, char Annee, char Heure, char Min, char Sec);
void RTC_Enable(void);
void RTC_Disable(void);
void RTC_GetTime(void);

#endif
