#pragma once
#include "GameObject.h"
class Coin :
    public GameObject
{
private:
    COINTYPE type;
    int CoinWorth;
public:
    std::string getType();
    int getCoinWorth();
    Coin();
    Coin(enum COINTYPE type);
    ~Coin();

    Coin* clone() const { return new Coin(*this); };
};

