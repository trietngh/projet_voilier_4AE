/**
 * @file Driver_ServoMoteur.h
 * @author  Louison TETAZ - Julie REVELLI - TANG Cam - NGUYEN Triet
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MYSERVO_H
#define MYSERVO_H
#include "stm32f10x.h"

void ServoMoteur_Move (short int angle);
void ServoMoteur_Init (void);

#endif
