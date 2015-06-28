# Arduino RF433 weather-station

## What it is

Simple external temp and humidity sensors, with Arduino Nano communicating to Arduino Leonardo through 433MHz radio components, and displaying the values on a 16x2 LCD display.

## How it works

### 1st part: transmitting data

The idea is to make a standalone sensor sending its data through short radio signal.
To retrieve instant temperature and humidity: I am using a DHT11 component.
To send short strings of data: I am using a RF 433 MHz TX module.
Both are Arduino compatibles and have to be used with their libraries.
Where I live, external temperature reach +40°C and go down to -10°C.
Humidity is a percentage, so technically values go from 0 to 100%.
Let's say that technically it will hardly exceed 99%... otherwise there's a real problem!
Now, let's group all this into one string:
1st digit will define whether it's a positive or negative temperature.
2nd and 3rd digits will define the absolute temperature value in Celsius.
4th and 5th digits will define the humidity.
As I don't care about decimals, I just always have to manage a 5 digits integer.
The LED is optionnal: I use it to visually check transmission.

### 2nd part: receiving and handling data

The idea is to make a standalone circuit, receiving data through radio signal, parsing data, and displaying the result.
To receive short strings of data: I am using a RF 433 MHz RX module.
To display data: I am using a standard 16x2 LCD display.
Both are Arduino compatibles and have to be used with their libraries.
The data received will be a 5 digits integer.
1st digit will define whether it's a positive or negative temperature.
2nd and 3rd digits will define the absolute temperature value in Celsius.
4th and 5th digits will define the humidity.
There are no decimals.
The LCD display is big enough to display these data plus - eventually - two more values for indoor temperature and room humidity.
The LED is optionnal: I use it to visually check receiving of data.

How to connect:
* LCD RS pin to digital pin 12
* LCD Enable pin to digital pin 10 (pin 11 = RX data)
* LCD D4 pin to digital pin 5
* LCD D5 pin to digital pin 4
* LCD D6 pin to digital pin 3
* LCD D7 pin to digital pin 2
* LCD R/W pin to ground
* 10K resistor:
* ends to +5V and ground
* wiper to LCD VO pin (pin 3)
* RX pin to digital pin 11

## What you get here

* INO files for transmitter (emetteurDHT11.ino) and receiver (recepteurLCD)
* Fritzing file for transmitter
* Demo picture

## What you need for this project

### Components

* 2x Arduino boards. I use:
  * Arduino Nano for the transmitter
  * Arduino Leonardo for the receiver
* 1x pair of RF 433Mhz modules, Arduino and VirtualWire compatibles
  * 1x transmitter
  * 1x receiver
* 1x DHT11 module, Arduino compatible
* 1x 16x2 LCD screen, Arduino compatible, with Hitachi HD44780 driver
* 1x 10K Ohm potentiometer
* 2x power supplies (for the Arduino boards)
* a few wires, including a 20-30cm wire to solder as an antenna
* 1x plastic box - optionnal - for the outdoor module
* 2x LEDs - optionnal - for visual feedback

### Tools

Nothing special. It depends if you want to solder or not. But I recommend you first prototype all this with your own requirements.

## Troubleshooting

This project is using Arduino 1.6.3 IDE. Due to old/obsolete/no-more-supported components I used, some Arduino 1.6.3 libraries may not be compatible.

One solution is to try using these .INO files with Arduino 1.0 or 0.2.3 IDE.

I'd rather keep using the 1.6.3 (or the last available version) so I edited the necessary libraries a little bit:

**VirtualWire.h** has been modified as follow:
```python
#include <wiring.h>
```
has been replaced with:
```python
#if ARDUINO >= 100
    #include <Arduino.h>
#else
    #include <wiring.h>
#endif
```

**VirtualWire.cpp** has been modified as follow:
```python
#include "WProgram.h"
```
has been replaced with:
```python
#include "Arduino.h"
```

## Useful links

* RF 433MHz demo: http://electroniqueamateur.blogspot.fr/2014/01/modules-rf-433-mhz-virtualwire-et.html
* Arduino Liquid Crystal tutorial: http://www.arduino.cc/en/Tutorial/LiquidCrysta
* LCD library: http://www.ladyada.net

## Todo list

* Complete project
* Complete connections description
* Add sensor to receiver to handle indoor temperature and humidity
* Eventually handle atmospheric pressure and logs for forecast
* Make a better display
* Handle clear screen and persistant display. I might have seen some script to clear the LCD display while keeping the values in memory...
* Make a better use of data in the transmitter part.
* Complete comments
* Add dependencies to Git repository
* Add more pictures
