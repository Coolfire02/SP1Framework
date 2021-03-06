 #pragma once
#include <Windows.h>
#include "MiniGame.h"
#include "Coin.h"
#include "Jar.h"
#include <stdlib.h>
#include <time.h>  

class MiniGame_RM :
    public MiniGame
{
private:
    std::string amount;
    int ms;
    int coin_spawn_delay;
    int coin_fall_delay;
    int coin, bigcoin, redcoin;
    std::vector<Coin*> coin_ptrs;
    Jar* jar_ptr;
    Text* Money_ptr;
    void addCoin(COORD);
public:
    void setMoneyText();
    std::string getType();
    enum LEVELSTATE getAssociatedLSState();

    MiniGame_RM(LEVEL level, Console& console);
    ~MiniGame_RM();

    void mgGameInit();
    void gameLoopListener();
    bool processKBEvents_mg(SKeyEvent KeyEvents[]);
    bool processMouseEvents_mg(SMouseEvent&);
    
    MiniGame_RM* clone() const { return new MiniGame_RM(*this); };
};

