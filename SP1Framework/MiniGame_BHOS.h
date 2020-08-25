#pragma once
#include "MiniGame.h"
#include "BeeHive.h"
class MiniGame_BHOS :
    public MiniGame
{
private:
    std::string amount;
    int ms;
    Text* Instructions;
    Text* Money_ptr;
    //BeeHive* Hive_ptr;
    COORD TreeMax, TreeMin;
    int numHive;
public:
    void setMoneyText();
    std::string getType();
    enum LEVELSTATE getAssociatedLSState();

    MiniGame_BHOS(LEVEL level, Console& console);
    ~MiniGame_BHOS();

    void mgGameInit();
    void gameLoopListener();
    bool processKBEvents(SKeyEvent KeyEvents[]);
    bool processMouseEvents(SMouseEvent&);
};

