#include "BeeHive.h"

std::string BeeHive::getType()
{
    if (type == BEEHIVE)
        return "BeeHive";
    else if (type == BEEHIVE_ICON)
        return "BeeHive_Icon";
}

int BeeHive::getHiveWorth()
{
    return HiveWorth;
}

BeeHive::BeeHive()
{
    type = BEEHIVE;
    art.setArt(BEEHIVE_ART);
    weight = 700;
    HiveWorth = 7;
    xMinHit = 25;
    xMaxHit = art.getXLength() + 35;
}

BeeHive::BeeHive(HIVETYPE Hivetype)
{
    type = BEEHIVE;
    if (Hivetype == BEEHIVE_ICON)
    {
        type = Hivetype;
        art.setArt(BEEHIVE_ICON_ART);
    }
    else if (Hivetype == BEEHIVE)
    {
        type = Hivetype;
        art.setArt(BEEHIVE_ART);
    }
    weight = 1100;
    HiveWorth = 7;
    xMinHit = 25;
    xMaxHit = art.getXLength() + 35;
}

BeeHive::~BeeHive()
{
    //Intentionally left blank
}
