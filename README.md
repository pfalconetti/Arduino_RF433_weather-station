# Arduino_RF433_weather-station
Simple external temp and humidity sensors, with Arduino Nano communicating to Arduino Leonardo through 433MHz radio components, and displaying the values on a 16x2 LCD display.

This project is using Arduino 1.6.3 IDE. Due to old/obsolete/no-more-supported components I used, some Arduino 1.6.3 libraries may not be compatible.
One solution is to try using these .INO files with Arduino 1.0 or 0.2.3 IDE.
I'd rather keep using the 1.6.3 (or the last available version) so I edited the necessary libraries a little bit:

- VirtualWire.h has been modified as follow:
      #include <wiring.h>
  has been replaced with:
      #if ARDUINO >= 100
        #include <Arduino.h>
      #else
        #include <wiring.h>
      #endif

- VirtualWire.cpp has been modified as follow:
      #include "WProgram.h"
  has been replaced with:
      #include "Arduino.h"

- More comments are available inline.

Work and english translations are still in progress...
