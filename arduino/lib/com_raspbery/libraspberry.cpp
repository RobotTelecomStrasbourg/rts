#include "libraspberry.h"

RaspberryCom::RaspberryCom(int address, int sizeReg)
{ 
  this->registre=new int[sizeReg];
  this->sizeReg = sizeReg;
  this->myAddress = address;
  this->flag_mode = FLAG_UNLOCKED;
  this->flag_run = FLAG_NEUTRAL;
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

void RaspberryCom::setMode(int flag)
{
  this->flag_mode = flag;
}

void RaspberryCom::setRun(int flag)
{
  this->flag_run = flag;
}

void RaspberryCom::waitRequest()
{
  this->flag_run = FLAG_WAITING;
  while (this->flag_run==FLAG_WAITING){ delay(100); }
}

void RaspberryCom::waitRequest(void(*fun)())
{
  this->flag_run = FLAG_WAITING;
  while (this->flag_run==FLAG_WAITING){ delay(100); }
  fun();
}





//  Fonction Annexe
//  Les fonctions onreceive et onrequest n'ont pas besoin d'etre appeler dans le code principal
//  
//  La fonction initCommunication est la seul fonction a utiliser ! 
void onreceive(int bc)
{
  Serial.println("Communication entrante"); 

  if (Wire.available())
  {
    int reg = Wire.read();
    int Nbyte = Wire.read();
    int type=Wire.read();
    Raspberry->last_type = type;
    
    if (type==TYPE_PUSH)
    {
      int flag = Wire.read();
      
      int v = 0; int tmp;
      for (int i=0;i<4;i++)
      {
        tmp = Wire.read();
        v = v | (tmp << (i*8));
      }
      
      Serial.println(reg);
      Serial.println(v);
      Raspberry->setMode(flag);
      Raspberry->setValue(reg,v);
      
      Raspberry->setRun(FLAG_NEUTRAL);
    }
    else if (type==TYPE_PULL)
    {
      Serial.println("Type PULL RECONNU");
      Raspberry->reg_last_pull = reg;
    }
  }
}

void onrequest()
{
  // TODO Coder la reponse du arduino <--> Raspberry
 
  if (Raspberry->last_type==TYPE_PULL)
  {
    Serial.println("Request :: TYPE_PULL");
    int v = Raspberry->getValue(Raspberry->reg_last_pull);
    for (int i=0;i<4;i++)
    {
    //  Wire.write((v>>(i*8)&0xFF));
    }
  }
  else if (Raspberry->flag_mode==FLAG_LOCKED)
  {
    while (Raspberry->flag_run==FLAG_RUNNING){ delay(200); }
    Wire.write(FLAG_UNLOCKED); 
  }
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

