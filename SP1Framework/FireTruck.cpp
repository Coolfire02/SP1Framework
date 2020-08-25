#include "FireTruck.h"

FireTruck::FireTruck(double maxWater) : maxWaterLevel(maxWater), currentWaterLevel(0);
{
    art.setArt(FIRE_TRUCK_ART);
    weight = 900;
}

FireTruck::~FireTruck()
{
}


std::string FireTruck::getType() {
    return "FireTruck";
}

void FireTruck::setMaxWaterLevel(double max)
{
    maxWaterLevel = max;
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
