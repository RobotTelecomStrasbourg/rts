#ifndef LIBRASPBERRY
#define LIBRASPBERRY

#include "Arduino.h"
#include <Wire.h>

// Type de requete
#define TYPE_PUSH 11
#define TYPE_PULL 12

// Reponse suite a un push ou non
#define FLAG_LOCKED 1
#define FLAG_UNLOCKED 2

class RaspberryCom
{
  private:
    int myAddress;
    int sizeReg;
    int * registre; 
  public:
    RaspberryCom(int address, int sizeReg);
    ~RaspberryCom();
    int getMyAddress();
    int getValue(int index);
    void setValue(int index, int value);
    void operator() (int byteCount);
    void operator() ();
};


// Variable global et fonction d'initialisation des communications
// Raspberry <--> Arduino
extern RaspberryCom* Raspberry;
void onreceive(int);
void onrequest();
void initCommunication(RaspberryCom* raspb);


#endif
