#pragma once
#include "MiniGame.h"
#include "Coin.h"
#include "Jar.h"

class MiniGame_RM :
    public MiniGame
{
private:
    int numCoin;
    int AmountofMoneyEarned;
    Coin* coin_ptr;
    Jar* jar_ptr;
    void addCoin();

public:
    std::string getType();
    enum LEVELSTATE getAssociatedLSState();
    MiniGame_RM(LEVEL level, Console& console);
    

    ~MiniGame_RM();

    bool processKBEvents(SKeyEvent KeyEvents[]);
    bool processMouseEvents(SMouseEvent&);

};

