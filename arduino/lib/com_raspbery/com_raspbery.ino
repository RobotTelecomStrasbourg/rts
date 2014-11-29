

#include "libraspberry.h"

#define address 0x10

Raspberry raspb(address, 2);
int led = 7;

void setup()
{
  // Configuration de la led
  pinMode(led, OUTPUT);
  
  initRaspberry(raspb);
  
  // Configuration de la communication Raspberry<->Arduino
  raspb.setValue(0, 100);
  raspb.setValue(1, 100);
}

void loop()
{
  digitalWrite(led, HIGH);
  delay((int)(raspb.getValue(0)));
  digitalWrite(led, LOW);
  delay(raspb.getValue(1));
}
