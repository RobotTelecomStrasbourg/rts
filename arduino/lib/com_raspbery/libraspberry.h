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

// Definition de l'etat d'execution
#define FLAG_WAITING 110
#define FLAG_RUNNING 111
#define FLAG_FINISH 112
#define FLAG_NEUTRAL 113



class RaspberryCom
{
  private:
    int reg_last_pull;
    int last_type;
    int flag_run;
    int flag_mode;
    int myAddress;
    int sizeReg;
    int * registre; 
  public:
    RaspberryCom(int address, int sizeReg);
    ~RaspberryCom();
    int getMyAddress();
    int getValue(int index);
    void setValue(int index, int value);
    void setMode(int flag);
    void setRun(int flag);
    void waitRequest();
    void waitRequest(void (*fun)() );
    
    friend void onreceive(int);
    friend void onrequest();
};


// Variable global et fonction d'initialisation des communications
// Raspberry <--> Arduino
extern RaspberryCom* Raspberry;
void onreceive(int);
void onrequest();
void initCommunication(RaspberryCom* raspb);


#endif
