/**
 * @file Driver_Girouette.h
 * @author Louison TETAZ - Julie REVELLI - TANG Cam - NGUYEN Triet 
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MYGIROUETTE_H
#define MYGIROUETTE_H
#include "stm32f10x.h"


void Girouette_Conf (void);
void Girouette_Init (void);
short int Girouette_GetAngle(void);
#endif
