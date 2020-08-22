#include "FireTruck.h"

FireTruck::FireTruck()
{
    currentWaterLevel = 100;
    MaxWaterLevel = 100;
    art.setArt(FIRE_TRUCK_ART);
    weight = 900;
}

FireTruck::~FireTruck()
{
}


std::string FireTruck::getType() {
    return "FireTruck";
}

void FireTruck::setMaxWaterLevel(int litres)
{
    MaxWaterLevel = litres;
}

void FireTruck::FillWater(int litres)
{
    if (currentWaterLevel < MaxWaterLevel)
    {
        if ((currentWaterLevel + litres) > MaxWaterLevel)
            currentWaterLevel = MaxWaterLevel;
        else
            currentWaterLevel += litres;
    }
}

bool FireTruck::MaxWaterFilled()
{
    bool isTankFull = false;
    if (currentWaterLevel == MaxWaterLevel)
        isTankFull = true;
    return isTankFull;
}

int FireTruck::getCurrentWaterLevel()
{
    return currentWaterLevel;
}
