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
  if (Wire.available())
  {
    int type=Wire.read();
    if (type==TYPE_PUSH)
    {
      Raspberry->setValue(0,100);
    }
    else
    {
      Raspberry->setValue(0,0);
    }
    
  }
  else
  {
    Raspberry->setValue(1,1000);
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

