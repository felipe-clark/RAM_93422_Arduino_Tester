/*******************************************************************************
 *                  Arduino memory tester for RAM 93422
 *******************************************************************************
 * Declaration of the functions to implement a simple user interface
 * -- Arduino IDE Version 1.8.13
 * -- Author: Felipe Sander Pereira Clark
 *
 * -- October, 2020
 *******************************************************************************/

#pragma once
#include "led_enumeration.h"

void waitForButton(void);
void driveLed(Led led, bool state);
void initLCD(void);
void printOnLCDLine(unsigned int line, const char* msg);
void printHexOnLCDLine(unsigned int line, int hex);
void clearLCDLine(unsigned int line);
void clearLCD(void);
