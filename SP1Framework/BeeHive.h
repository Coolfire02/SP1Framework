#pragma once
#include "GameObject.h"
class BeeHive :
    public GameObject
{
private:
    int xMinHit;//To check whether the mouse reaches the minimum boundary (BHOS)
    int xMaxHit;//To check whether the mouse overshot
    int HiveWorth;
    HIVETYPE type;
public:
    std::string getType();
    int getHiveWorth();
    BeeHive();
    BeeHive(HIVETYPE Hivetype);
    ~BeeHive();

    BeeHive* clone() const { return new BeeHive(*this); };
};

