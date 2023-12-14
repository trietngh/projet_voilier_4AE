#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_ADC.h"
#include "Driver_Girouette.h"

MyGPIO_Struct_TypeDef MonPWM = {GPIOB, 6, AltOut_Ppull};
MyTimer_Struct_TypeDef MonTIM = {TIM4, 1599, 899};

void ServoMoteur_Init(void)
{
	
	//initialisation pwm
	MyGPIO_Init(&MonPWM);
	MyTimer_Base_Init(&MonTIM);
	
	MyTimer_PWM(TIM4, 1);
	MyTimer_PWM_DutyCycle(&MonTIM, 1, 10);
	
	MyTimer_Base_Start(TIM4);
}

void ServoMoteur (short angle)
{	
	//10% fermer les voiles
	//5% ouvrir completement les voiles
	//on ouvre les voiles selon le vent 
	if (45 <= angle && angle <= 315 )
	{
		if (angle > 180){
			angle = 360 - angle;
		}
		MyTimer_PWM_DutyCycle(&MonTIM, 1, 10 - ((angle - 45)*5/135));
	}
	else
	{
		MyTimer_PWM_DutyCycle(&MonTIM, 1, 10); //on ferme les voiles
	} 
}
