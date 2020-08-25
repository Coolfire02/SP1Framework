#include "BeeHive.h"

std::string BeeHive::getType()
{
    return "BeeHive";
}

int BeeHive::getHiveWorth()
{
    return HiveWorth;
}

BeeHive::BeeHive()
{
    art.setArt(BEEHIVE_ART);
    weight = 700;
    HiveWorth = 1000;
    xMinHit = 25;
    xMaxHit = art.getXLength() + 35;
}

BeeHive::~BeeHive()
{
    //Intentionally left blank
}
