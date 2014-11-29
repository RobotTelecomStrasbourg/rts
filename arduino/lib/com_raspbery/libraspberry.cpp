#include "libraspberry.h"


Raspberry::Raspberry(int address, int sizeReg)
{
  this->registre=new int[sizeReg];
  this->sizeReg = sizeReg;
  this->myAddress = address;
}

Raspberry::~Raspberry()
{
  delete[] this->registre;
}

int Raspberry::getValue(int index)
{
  return this->registre[index];
}

void Raspberry::setValue(int index, int value)
{
  this->registre[index] = value;
}

void Raspberry::operator()(int byteCount)
{
  if (Wire.available())
  {
    int type = Wire.read();
  
    if (type==TYPE_PUSH)
    {
      this->setValue(0,500);
    }
    else 
    {
      this->setValue(1,200);
    }
  }
  else
  {
    this->setValue(1,500);
  }
}

void Raspberry::operator()()
{
  // TODO
}

int Raspberry::getMyAddress()
{
  return this->myAddress;
}

void initRaspberry(Raspberry raspberry)
{
  Wire.begin(raspberry.getMyAddress());
  Wire.onReceive((void(*)(int))&raspberry);
  Wire.onRequest((void(*)())&raspberry);
}


