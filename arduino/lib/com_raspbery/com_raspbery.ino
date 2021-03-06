

#include <Wire.h>
#include "libraspberry.h"

#define address 0x10

int k=0;
int led = 7;

void setup()
{
  // Configuration de la led
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  
  // Configuration de la communication Raspberry<->Arduino
  // initCommunication Obligatoire !  
  initCommunication(new RaspberryCom(address, 2));
  Raspberry->setValue(0,1000);
  Raspberry->setValue(1,1000); 
}


void function()
{
   Serial.println("RUN ! ");
}


void loop()
{
  if (k==0)
  {
    Raspberry->waitRequest(function);
    k=1;
  }
  
  //Serial.println(raspberry->getValue(0));
  digitalWrite(led, HIGH);
  delay(Raspberry->getValue(0));
  digitalWrite(led, LOW);
  delay(Raspberry->getValue(1));
}
