/*******************************************************************************
 *                  Arduino memory tester for RAM 93422
 *******************************************************************************
 * Definition of the functions to implement a simple user interface
 * -- Arduino IDE Version 1.8.13
 * -- Author: Felipe Sander Pereira Clark
 *
 * -- October, 2020
 *******************************************************************************/

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <avr/sleep.h>
#include "board_setup.h"
#include "user_interface.h"
#include "led_enumeration.h"

static LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x2, 16 columns and 2 rows

void wakeUp(void)
{
    sleep_disable();
    detachInterrupt(digitalPinToInterrupt(startBtn));
}

void waitForButton(void)
{
    while (digitalRead(startBtn) == LOW)
    {
        /* Sleeps for 100 microseconds to save energy.
         * TODO: in the future, let's use avr/sleep.h
         * and further save power by shutting down the
         * board and waking it up with an interrupt.
         */
        delayMicroseconds(100);
    }

    driveLed(Led::Green, LOW);
    driveLed(Led::Red, LOW);
}

void driveLed(Led led, bool state)
{
    switch (led)
    {
    case Led::Green:
        digitalWrite(greenLed, state);
        break;
    case Led::Red:
        digitalWrite(redLed, state);
        break;
    }
}

void initLCD(void)
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void clearLCDLine(unsigned int line)
{
    lcd.setCursor(0, line);
    lcd.print("                ");
    lcd.setCursor(0, line);
}

void printOnLCDLine(unsigned int line, const char* msg)
{
    clearLCDLine(line);
    lcd.print(msg);
}

void printHexOnLCDLine(unsigned int line, int hex)
{
    char msg[17];
    sprintf(msg, "0x%02X", hex);

    printOnLCDLine(line, msg);
}

void clearLCD(void)
{
    lcd.clear();
}

