/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
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
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

/************************************************************** 
 * Affiche sur le moniteur serie le nombre entier reçu.
 * Sketch du récepteur (branché à la pin 11, par défaut).
 * http://electroniqueamateur.blogspot.com/2014/01/modules-rf-433-mhz-virtualwire-et.html
 * PPF: Voir script de l'émetteur pour les corrections de libs.
 ***************************************************************/

// FIXME PPF: gérer l'effacement de la rémanance de l'affichage
// Il me semble avoir vu un script sur le Net pour effacer l'affichage en conservant sa valeur
// FIXME PPF: ajouter le circuit de pression atmosphérique
// FIXME PPF: gérer les infos envoyées par le TX (temp + humidité)
// FIXME PPF: soigner les infos affichées

int led = 13;
int absdegres = 12;
int negatif = 2;
int humidite = 0;

// LCD 16x02
// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 10, 5, 4, 3, 2);

// RX 433MHz
#include <VirtualWire.h>
int Nombre;
char Message[VW_MAX_MESSAGE_LEN];

void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
  
  // RX 433MHz
  vw_setup(2000);   // Bits par seconde   
  vw_rx_start();       

  // LCD 16x02
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

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
    // Conversion du tableau de chars en int:
    Nombre = atoi(Message);
    // Ligne dessus
    lcd.setCursor(0, 0);
    lcd.print("int ..C");
    lcd.setCursor(8, 0);
    lcd.print(".... Hpa");
    // Ligne dessous
    lcd.setCursor(0, 1);
    lcd.print("ext ...C");
    lcd.setCursor(9, 1);
    lcd.print("..% hum");
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
