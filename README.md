# Arduino RF433 weather-station

## What it is

Simple external temp and humidity sensors, with Arduino Nano communicating to Arduino Leonardo through 433MHz radio components, and displaying the values on a 16x2 LCD display.

## How it works

### 1st part: transmitting data

The idea is to make a standalone sensor sending its data through short radio signal.
To retrieve instant temperature and humidity: I am using a DHT11 component.
To send short strings of data: I am using a RF 433 MHz module.
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

...

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

## Todo list

- More comments are available inline.

Work and english translations are still in progress...
