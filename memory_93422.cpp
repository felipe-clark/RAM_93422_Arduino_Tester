/*******************************************************************************
 *                  Arduino memory tester for RAM 93422
 *******************************************************************************
 * Definition of the functions to communicate with the 93422 RAM chip
 * -- Arduino IDE Version 1.8.13
 * -- Author: Felipe Sander Pereira Clark
 *
 * -- October, 2020
 *******************************************************************************/

#include <Arduino.h>
#include <math.h> //For pow()
#include "memory_93422.h"
#include "board_setup.h"
#include "user_interface.h"

static const int maxAddr = pow(2, nrAddressPins) - 1;

/* This function puts the memory disabled
 * state (not enabled, not reading and not
 * writing).
 */
static void setMemoryZ()
{
    digitalWrite(memoryEnable, LOW);
    digitalWrite(memoryWrite, HIGH);
    digitalWrite(memoryEnable, HIGH);
}

/* This function will only put the memory in
 * write mode. It will not guarantee that the
 * memory chip is enabled.
 */
static void setMemoryWrite()
{
    // Enable write function
    digitalWrite(memoryWrite, LOW);
    // Disable read function
    digitalWrite(memoryRead, HIGH);
}

/* This function will only put the memory in
 * read mode. It will not guarantee that the
 * memory chip is enabled.
 */
static void setMemoryRead()
{
    // Enable read function
    digitalWrite(memoryRead, LOW);
    // Disable write function
    digitalWrite(memoryWrite, HIGH);
}

void writeMemory(uint8_t data)
{
    setMemoryWrite();

    for (int addr = 0; addr <= maxAddr; addr++)
    {
        printHexOnLCDLine(1, addr);
        digitalWrite(memoryEnable, LOW);
        putAddrOnBus(addr);
        putDataOnBus(data);
        digitalWrite(memoryEnable, HIGH);

        /* Give 1us for the data to be
         * written by the memory
         */
        delayMicroseconds(1);
    }

    setMemoryZ();
}

bool readMemory(uint8_t expectedData)
{
    bool success = true;
    uint8_t readData = 0x0;
    
    setMemoryRead();

    for (int addr = 0; addr <= maxAddr; addr++)
    {
        printHexOnLCDLine(1, addr);
        digitalWrite(memoryEnable, LOW);
        putAddrOnBus(addr);
        digitalWrite(memoryEnable, HIGH);

        /* Give 1us for the data to be
         * output by the memory
         */
        delayMicroseconds(1);

        if (expectedData != (readData = readDataFromBus()))
        {
            Serial.print("Test failed at addr: ");
            Serial.println(addr);
            success = false;
            break;
        }
    }

    if (success)
        clearLCDLine(1);

    setMemoryZ();

    return success;

}

void putAddrOnBus(uint8_t addr)
{
    for (int pinOffset = 0; pinOffset < nrAddressPins; pinOffset++)
    {
        digitalWrite(addrOutputPins[pinOffset], (addr >> pinOffset) & 0x01);
    }
}

void putDataOnBus(uint8_t data)
{
    for (int pinOffset = 0; pinOffset < nrDataInOutPins; pinOffset++)
    {
        digitalWrite(dataOutputPins[pinOffset], (data >> pinOffset) & 0x01);
    }
}

uint8_t readDataFromBus()
{
    uint8_t dataRead = 0x00;

    for (int pinOffset = 0; pinOffset < nrDataInOutPins; pinOffset++)
    {
        dataRead <<= 1;
        dataRead |= digitalRead(dataInputPins[pinOffset]);
    }

    return dataRead;
}
