/*
  ARDUINO RECEIVER WITH LCD DISPLAY

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
*/

// What we need for radio TX/RX
#include <VirtualWire.h>
int Nombre;
char Message[VW_MAX_MESSAGE_LEN];

// What we need for Hitachi HD44780 16x2 LCD display
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 10, 5, 4, 3, 2); // Initialize the library with the numbers of the interface pins

//  Vars
int absDeg = 12; // Temperature in Celsius (2 digits, no decimal)
int isNeg = 2;   // 1 digit defining sign of temperature: 2 for positive, 1 for negative 
int moist = 0;   // 2 digits for humidity: from 00% to 99%
int led = 13;    // LED for visual feedback

void setup() {
  pinMode(led, OUTPUT);     
  vw_setup(2000); // Transmission rate: bits per second
  vw_rx_start();       
  lcd.begin(16, 2); // LCD 16x02: set up the LCD's number of columns and rows: 
  digitalWrite(led, LOW);
}

void loop() {
  digitalWrite(led, LOW);
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if (vw_get_message(buf, &buflen)) {
    digitalWrite(led, HIGH);
    delay(50);
    int i;
    for (i=0; i<buflen; i++) {               
      Message[i] = char(buf[i]);
    }
    Message[buflen] = '\0';
    // Data conversion: chars table into integer
    Nombre = atoi(Message);
    // 1st LCD line of constant display
    lcd.setCursor(0, 0);
    lcd.print("int ..C");
    lcd.setCursor(8, 0);
    lcd.print(".... Hpa");
    // 2nd LCD line of constant display
    lcd.setCursor(0, 1);
    lcd.print("ext ...C");
    lcd.setCursor(9, 1);
    lcd.print("..% hum");
    // 2nd LCD line of data display
    lcd.setCursor(4, 1);
    if(char(buf[0])==1) {
      lcd.print("-");
    } else {
      lcd.print("+");
    }
    lcd.setCursor(5, 1);
    lcd.print(char(buf[1]));
    lcd.setCursor(6, 1);
    lcd.print(char(buf[2]));
    lcd.setCursor(9, 1);
    lcd.print(char(buf[3]));
    lcd.setCursor(10, 1);
    lcd.print(char(buf[4]));
  }
}
