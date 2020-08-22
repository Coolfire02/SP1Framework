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
    std::vector<Coin*> coin_ptrs;
    Jar* jar_ptr;
    void addCoin(COORD);
public:
    std::string getType();
    enum LEVELSTATE getAssociatedLSState();
    MiniGame_RM(LEVEL level, Console& console);

    ~MiniGame_RM();

    void gameLoopListener();
    bool processKBEvents(SKeyEvent KeyEvents[]);
    bool processMouseEvents(SMouseEvent&);

};

