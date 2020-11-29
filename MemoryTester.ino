/*******************************************************************************
 *                  Arduino memory tester for RAM 93422
 *******************************************************************************
 * -- Arduino IDE Version 1.8.13
 * -- Author: Felipe Sander Pereira Clark
 * 
 * -- Required libraries: LiquidCrystal_I2C
 * To install libraries, go to Tools->Manage Libraries and search for the names
 * listed above in the Arduino IDE.
 *
 * -- October, 2020
 *******************************************************************************/

#include "board_setup.h"
#include "memory_93422.h"
#include "state_enumeration.h"
#include "led_enumeration.h"
#include "user_interface.h"

static State currentState = State::WAITING_FOR_BUTTON;
uint8_t addrOutputPins[nrAddressPins];
uint8_t dataOutputPins[nrDataInOutPins];    // Input to 93422 Chip
uint8_t dataInputPins[nrDataInOutPins];     // Output from 93422 Chip

void setup() {
    // Setting up memory address pins
    for (int pinOffset = 0; pinOffset < nrAddressPins; pinOffset++)
    {
        addrOutputPins[pinOffset] = addrBasePin + pinOffset;
        pinMode(addrOutputPins[pinOffset], OUTPUT);
        digitalWrite(addrOutputPins[pinOffset], LOW);
    }

    // Setting up data input/output pins
    for (int pinOffset = 0; pinOffset < nrDataInOutPins; pinOffset++)
    {
        dataOutputPins[pinOffset] = dataInputBasePin + pinOffset;
        pinMode(dataOutputPins[pinOffset], OUTPUT);
        digitalWrite(dataOutputPins[pinOffset], LOW);

        dataInputPins[pinOffset] = dataOutputBasePin + pinOffset;
        pinMode(dataInputPins[pinOffset], INPUT);
    }

    // Start the circuit with the memory disabled
    // !CS0 will be permanently set to 0. We will
    // control memory enablement only via CS1
    pinMode(memoryEnable, OUTPUT);
    pinMode(memoryEnableInv, OUTPUT);
    digitalWrite(memoryEnable, LOW);
    digitalWrite(memoryEnableInv, LOW);

    // Start the circuit with no memory function selected
    pinMode(memoryWrite, OUTPUT);
    digitalWrite(memoryWrite, HIGH);

    pinMode(memoryRead, OUTPUT);
    digitalWrite(memoryRead, HIGH);

    // Starts with green LED on to indicate
    // circuit is waiting for user command
    pinMode(greenLed, OUTPUT);
    //digitalWrite(greenLed, HIGH);

    pinMode(redLed, OUTPUT);
    digitalWrite(greenLed, LOW);

    pinMode(startBtn, INPUT);

    initLCD();

    Serial.begin(9600);
    Serial.println("");
}

void loop() {

    // State machine runs forever
    switch (currentState)
    {
    case State::WAITING_FOR_BUTTON:
        clearLCD();
        printOnLCDLine(0, "Press start");
        Serial.println("Press start");
        waitForButton();
        currentState = State::WRITE_MEMORY_ONES;
        break;
    case State::WRITE_MEMORY_ONES:
        printOnLCDLine(0, "Writing 1s");
        writeMemory(0xF);
        currentState = State::READ_MEMORY_ONES;
        break;
    case State::READ_MEMORY_ONES:
        printOnLCDLine(0, "Reading 1s");
        currentState = readMemory(0xF) ? State::WRITE_MEMORY_ZEROS : State::FAILURE;
        break;
    case State::WRITE_MEMORY_ZEROS:
        printOnLCDLine(0, "Writing 0s");
        writeMemory(0x0);
        currentState = State::READ_MEMORY_ZEROS;
        break;
    case State::READ_MEMORY_ZEROS:
        printOnLCDLine(0, "Reading 0s");
        currentState = readMemory(0x0) ? State::SUCCESS : State::FAILURE;
        break;
    case State::FAILURE:
        printOnLCDLine(0, "Test failed");
        driveLed(Led::Red, HIGH);
        delay(5000);
        currentState = State::WAITING_FOR_BUTTON;
        break;
    case State::SUCCESS:
        printOnLCDLine(0, "Test successful");
        Serial.println("Test successful");
        driveLed(Led::Green, HIGH);
        delay(5000);
        currentState = State::WAITING_FOR_BUTTON;
        break;
    case State::ABORT:
        printOnLCDLine(0, "Fatal error");
        printOnLCDLine(1, "Reboot required");
        while (true) { /* No operation */ }
        break;
    default:
        currentState = State::ABORT;
    }
}
