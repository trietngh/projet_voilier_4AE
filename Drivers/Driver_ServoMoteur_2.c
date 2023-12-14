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

void ServoMoteur (short int angle)
{
	if (angle > 45*4 && angle < 180*4) //de 45 à 180° 
	{
		MyTimer_PWM_DutyCycle(&MonTIM, 1, ((-4./27.) * (((angle/4)-45)/5) + 10)); //changer le rapport cyclique entre 10 et 5%
	}
	else if (angle < (-180*4) && angle > (-315*4)) //de -180 à -315° 
	{
		MyTimer_PWM_DutyCycle(&MonTIM, 1, ((4./27.) * (-1*((angle/4)+180)/5) + 5)); //changer le rapport cyclique entre 5 et 10%
	}
	else if (angle < (-45*4) && angle > (-180*4)) //de -45 à -180° 
	{
		MyTimer_PWM_DutyCycle(&MonTIM, 1, ((-4./27.) * (-1*((angle/4)+45)/5) + 10)); //changer le rapport cyclique entre 10 et 5%
	}
	else if (angle > 180*4 && angle < 315*4) //de 180 à 315°
	{
		MyTimer_PWM_DutyCycle(&MonTIM, 1, ((4./27.) * (((angle/4)-180)/5) + 5)); //changer le rapport cyclique entre 5 et 10%
	}
	else
	{
		MyTimer_PWM_DutyCycle(&MonTIM, 1, 10); //de 0 à 45° ou de 0 à -45° on ferme les voiles
	} 
}
