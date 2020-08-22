#pragma once
#include "MiniGame.h"

class MiniGame_WL : public MiniGame
{
public:
    enum LEVELSTATE getAssociatedLSState();
    MiniGame_WL(LEVEL level, Console& console);
    ~MiniGame_WL();



    bool processKBEvents(SKeyEvent[]);
    bool processMouseEvents(SMouseEvent&);
    std::string getType();
};

