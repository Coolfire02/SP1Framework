#pragma once
#include "MiniGame.h"

class MiniGame_WL : public MiniGame
{
private:
    std::string getType();
  
public:
    enum LEVELSTATE getAssociatedLSState();
    MiniGame_WL();
    ~MiniGame_WL();
};
