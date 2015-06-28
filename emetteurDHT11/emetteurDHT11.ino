/*
  ARDUINO TEMPERATURE AND HUMIDITY TRANSMITTER
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
*/

// What we need for radio TX/RX
#include <VirtualWire.h>
int absDeg = 0; // 2 digits for temperature (no decimal)
int isNeg = 2;  // 1 digit defining sign of temperature: 2 for positive, 1 for negative 
int moist = 0;  // 2 digits for humidity: from 00% to 99%
int TXstr = 0;  // 5 digits
int led = 13;   // LED for visual feedback
char Message[VW_MAX_MESSAGE_LEN]; 

// What we need for weather
#include <dht.h>
dht DHT;
#define DHT11_PIN 5

void setup() {
  pinMode(led, OUTPUT);     
  vw_setup(2000); // Transmission rate: bits per second
}

void loop() {
  int chk = DHT.read11(DHT11_PIN); // Property and method (!)
  // Writing temperature on 3 digits
  absDeg = DHT.temperature;
  if (absDeg < 0) {
    absDeg = abs(DHT.temperature);
    isNeg = 1;
  } else {
    absDeg = DHT.temperature;
    isNeg = 2;
  }
  if(absDeg > 99) {absDeg = 99;}
  // Writing humidity on 2 digits
  moist = DHT.humidity;
  if (moist < 0)  {moist = 0;}
  if (moist > 99) {moist = 99;}
  // All values into one unique integer
  TXstr = isNeg*10000 + absDeg*100 + moist;
  // Converting integer to tab of chars
  itoa(TXstr, Message, 10);  // "10" stands for decimal
  // TX sequence
  digitalWrite(led, HIGH);
  vw_send((uint8_t *)Message, strlen(Message));
  vw_wait_tx(); // Waiting for end of transmission
  digitalWrite(led, LOW);
  delay(2000);  // Taking a little bit of rest...
}
