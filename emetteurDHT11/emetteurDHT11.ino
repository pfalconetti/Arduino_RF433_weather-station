// Partie radio
#include <VirtualWire.h>
int absdegres = 0;
int negatif = 2;
int humidite = 0;
int chaine = 0;
int led = 13;
char Message[VW_MAX_MESSAGE_LEN]; 

// Partie météo
#include <dht.h>
dht DHT;
#define DHT11_PIN 5

void setup() {
  pinMode(led, OUTPUT);     
  vw_setup(2000); // bits de transmission par seconde
}

void loop() {
  int chk = DHT.read11(DHT11_PIN); // propriété ET méthode !
  absdegres = DHT.temperature;
  if(absdegres < 0) {
    absdegres = abs(DHT.temperature);
    negatif = 1;
  } else {
    absdegres = DHT.temperature;
    negatif = 2;
  }
  if(absdegres > 99) {absdegres = 99;}
  humidite = DHT.humidity;
  if(humidite < 0)  {humidite = 0;}
  if(humidite > 99) {humidite = 99;}
  // Valeurs
  chaine = negatif*10000 + absdegres*100 + humidite;
  // Conversion du int en tableau de chars 
  itoa(chaine,Message,10);  // 10 car décimal
  // Séquence de transmission
  digitalWrite(led, HIGH);
  vw_send((uint8_t *)Message, strlen(Message));
  vw_wait_tx(); // On attend la fin de la transmission
  digitalWrite(led, LOW);
  delay(2000);  // et on se repose un peu...
}