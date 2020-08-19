#pragma once
#include "MiniGame.h"
#include "ASCII.h"
class MiniGame_WL : public MiniGame
{
private:
    ASCII MGascii;
    std::string getType();
};

