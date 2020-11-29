/*******************************************************************************
 *                  Arduino memory tester for RAM 93422
 *******************************************************************************
 * Declaration of the functions to communicate with the 93422 RAM chip
 * -- Arduino IDE Version 1.8.13
 * -- Author: Felipe Sander Pereira Clark
 *
 * -- October, 2020
 *******************************************************************************/

#pragma once

#include <stdint.h> //For uint8_t without having to include all of Arduino.h

void writeMemory(uint8_t data);
bool readMemory(uint8_t expectedData);
void putAddrOnBus(uint8_t addr);
void putDataOnBus(uint8_t addr);
uint8_t readDataFromBus();
