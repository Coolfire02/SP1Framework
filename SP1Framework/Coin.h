#pragma once
#include "GameObject.h"
class Coin :
    public GameObject
{
private:
    int CoinWorth;
public:
    std::string getType();
    int getCoinWorth();
    Coin();
    ~Coin();
};

