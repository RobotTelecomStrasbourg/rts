#include <Wire.h>


#define I2C_ADDRESS 0x10

int led = 7;
int i2c_data = 1;
int dtime = 1000;

void setup()
{
  // Configuration du bus i2c
  Serial.begin(9600);
  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  // Configuration de la sortie LED
  pinMode(led, OUTPUT);
}

// Fonction appeler a la reception de donne
void receiveData(int byteCount)
{
  // Tant qu'il y a  des donnes en attente les lire  
  while(Wire.available()) 
  {
      i2c_data = Wire.read();
      Serial.print("Donnee recue par i2c : ");
      Serial.println(i2c_data);
  }
}

// Fonction declencher a la reception de donnee par le protocole I2C
void sendData()
{
  int send_data = i2c_data + 1; 
  Wire.write(send_data);
  
  
  Serial.print("Donnee envoye : ");
  Serial.println(send_data);
}


// 
void loop()
{
  
  if (i2c_data==11)
  {
    dtime = 1000;
  }
  else
  {
    dtime = 500; 
    
  }
  
  digitalWrite(led, HIGH);
  delay(dtime);
  digitalWrite(led, LOW);
  delay(dtime);

}
