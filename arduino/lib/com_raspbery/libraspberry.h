#ifndef LIBRASPBERRY
#define LIBRASPBERRY


// Type de requete
#define TYPE_PUSH 11
#define TYPE_PULL 12

// Reponse suite a un push ou non
#define FLAG_LOCKED 1
#define FLAG_UNLOCKED 2



class Raspberry
{
  private:
    int myAddress;
    int sizeReg;
    int * registre; 
  public:
    Raspberry(int address, int sizeReg);
    ~Raspberry();
    int getMyAddress();
    int getValue(int index);
    void setValue(int index, int value);
    void operator() (int byteCount);
    void operator() ();
};

//void initRaspberry(Raspberry raspberry);



#endif
