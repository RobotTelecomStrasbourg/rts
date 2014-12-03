#include "libraspberry.h"

RaspberryCom::RaspberryCom(int address, int sizeReg)
{ 
  this->registre=new int[sizeReg];
  this->sizeReg = sizeReg;
  this->myAddress = address;
}


RaspberryCom::~RaspberryCom()
{
  delete[] this->registre;
}

int RaspberryCom::getValue(int index)
{
  return this->registre[index];
}

void RaspberryCom::setValue(int index, int value)
{
  this->registre[index] = value;
}

int RaspberryCom::getMyAddress()
{
  return this->myAddress;
}



// 
//
//
void onreceive(int bc)
{
  Serial.println("Communication entrante");
  //Serial.print("Nombre d'octet en entré = ");
  Serial.println(bc);
  
  /*
  while (Wire.available())
  {
    Serial.println(Wire.read());
  }
  */
  if (Wire.available())
  {
    int reg = Wire.read();
    int Nbyte = Wire.read();
    int type=Wire.read();
    
    if (type==TYPE_PUSH)
    {
      int flag = Wire.read();
      
      int v = 0; int tmp;
      for (int i=0;i<4;i++)
      {
        tmp = Wire.read();
        v = v | (tmp << (i*8));
      }
      if (flag==FLAG_LOCKED)
      {
        // TODO Gerer le processus bloquant
      }
      Serial.println(reg);
      Serial.println(v);
      Raspberry->setValue(reg,v);
    }
    else
    {
      Serial.println("Type PULL RECONNU");
      // TODO Envoyer la value
    }
  }
  else
  {
    // ERREUR DE TRANSMISSION
  }
}

void onrequest()
{
  // TODO Coder la reponse du arduino <--> Raspberry
}  
  
void initCommunication(RaspberryCom* raspberry)
{
  Raspberry = raspberry;
  
  Serial.begin(9600);
  Wire.begin(Raspberry->getMyAddress());
  Wire.onReceive(onreceive);
  Wire.onRequest(onrequest);
}
RaspberryCom* Raspberry = 0;

