/**
 * @file Driver_RTC.h
 * @author TANG Cam - NGUYEN Triet 
 * @date 2023-12-15
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MYROULIS_H
#define MYROULIS_H

#include "stm32f10x.h"
#include <stdbool.h>
#include "MySPI.h"

#define ROULIS_SPI SPI2

/* Init the accelerometer for mesuring angle */
void ROULIS_Init(void);
/* Check if the tilt of the boat exceed the limit of 40� */
bool ROULIS_CheckTiltLimit(void);

#endif
