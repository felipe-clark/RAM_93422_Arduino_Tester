# RAM_93422_Arduino_Tester

This is an Arduino project that configures an Arduino Mega board to test a 93422 Random Access Memory (RAM) chip. The test will write 1s and 0s to every address and read back the values, indicating failure when there is a discrepancy.
Dependency: LiquidCrystal I2C library by Frank de Brabander
To install libraries go to Tools->Manage Libraries and search for the name listed above in the Arduino IDE.

This project is provided as-is. Feel free to fork, use and modify it freely. If you would like to propose some change, please submit a merge request.

The following table describes the pin connections to setup the circuit:

CONNECTION TABLE
Arduino pin|Other component
-----------|---------------
22|Green LED
23|Red LED
24|93422 PIN 19
30|93422 PIN 4
31|93422 PIN 3
32|93422 PIN 2
33|93422 PIN 1
34|93422 PIN 21
35|93422 PIN 5
36|93422 PIN 6
37|93422 PIN 7
39|Start button
43|93422 PIN 9
44|93422 PIN 11
45|93422 PIN 13
46|93422 PIN 15
47|93422 PIN 10
48|93422 PIN 12
49|93422 PIN 14
50|93422 PIN 16
51|93422 PIN 17
52|93422 PIN 20
53|93422 PIN 18
SCA|16x2 I2C LCD matrix
SDL|16x2 I2C LCD matrix

It is recommended to have 1k resistors on each of the Arduino's outputs to limit the current.
Please read file board_setup.h for more information.


To start the memory test it suffices to press the button connected to pin 39. This button must bring the logic level on the pin to HIGH. Notice that a hardware debouncer is recommended.
This project is meant to use an I2C 16x2 LCD matrix on address 0x27. However, if you do not have such display, you can also read the diagnosis from the serial console on your computer.
The two LEDs are also used to communicate the diagnostic. Green will be light up after the initial boot. After the button is pressed and the test is completed, green indicates success and red indicates failure. The same information will be communicated on the LCD display with more details (such as the tested addresses and in which address the test failed). The LCD will hold the diagnostic information for 5 seconds after the test finishes, but the LEDs will permanently indicate failure/success until the test is initiated again by a press of the start button.