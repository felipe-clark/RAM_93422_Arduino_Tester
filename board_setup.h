/*******************************************************************************
 *                  Arduino memory tester for RAM 93422
 *******************************************************************************
 * Declaration of the board configuration (pin map)
 * -- Arduino IDE Version 1.8.13
 * -- Author: Felipe Sander Pereira Clark
 *
 * -- October, 2020
 *******************************************************************************/

#pragma once
#include <stdint.h> //For uint8_t without having to include all of Arduino.h

constexpr const int memoryEnableInv = 24; // Memory Enable: active LOW (!CS)
constexpr const int memoryEnable = 51; // Memory Enable: active HIGH (CS)
constexpr const int memoryWrite = 52; // Write Enable: active LOW (!WE) 
constexpr const int memoryRead = 53; // Output Enable: active LOW (!OE)
constexpr const int startBtn = 39; // Active HIGH
constexpr const int greenLed = 22; // Success indicator: active HIGH
constexpr const int redLed = 23; // Failure indicator: active LOW
constexpr const int nrAddressPins = 8;
constexpr const int nrDataInOutPins = 4;
constexpr const int addrBasePin = 30;
constexpr const int dataInputBasePin = 43;
constexpr const int dataOutputBasePin = 47;

/* Making these pin groups visible from other
 * files in the project that include this header.
 * These groups are defined in MemoryTester.ino
 */
extern uint8_t addrOutputPins[nrAddressPins];
extern uint8_t dataOutputPins[nrDataInOutPins];    // Input to 93422 Chip
extern uint8_t dataInputPins[nrDataInOutPins];     // Output from 93422 Chip



/*
 * CONNECTION TABLE (FOR REFERENCE)
 * 
 * Arduino pin	Other component
 * 22			Green LED
 * 23			Red LED
 * 24			93422 PIN 19
 *
 * 30			93422 PIN 4
 * 31			93422 PIN 3
 * 32			93422 PIN 2
 * 33			93422 PIN 1
 * 34			93422 PIN 21
 * 35			93422 PIN 5
 * 36			93422 PIN 6
 * 37			93422 PIN 7
 * 
 * 39			Start button
 *
 * 43			93422 PIN 9
 * 44			93422 PIN 11
 * 45			93422 PIN 13
 * 46			93422 PIN 15
 * 47			93422 PIN 10
 * 48			93422 PIN 12
 * 49			93422 PIN 14
 * 50			93422 PIN 16
 * 51			93422 PIN 17
 * 52			93422 PIN 20
 * 53			93422 PIN 18
 * 
 * SCA			16x2 LCD matrix
 * SDL			16x2 LCD matrix
 */
