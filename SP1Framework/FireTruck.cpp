#include "FireTruck.h"

FireTruck::FireTruck(double maxWater) : maxWaterLevel(maxWater), currentWaterLevel(0)
{
    direction = T_RIGHT;
    art.setArt(FIRE_TRUCK_ART);
    weight = 900;
}

FireTruck::~FireTruck()
{
}

void FireTruck::setDirection(TRUCK_DIRECTION direc) {
    if (direc == direction) return;
    direction = direc;
    switch (direc) {
    case T_LEFT:
        art.setArt(FIRE_TRUCK_LEFT_ART);
        break;
    case T_RIGHT:
        art.setArt(FIRE_TRUCK_ART);
        break;
    }
}


std::string FireTruck::getType() {
    return "FireTruck";
}

void FireTruck::setMaxWaterLevel(double max)
{
    maxWaterLevel = max;
}

void FireTruck::setWaterLevel(double max)
{
    currentWaterLevel = max;
}

void FireTruck::FillWater(double litres)
{
    if (currentWaterLevel < maxWaterLevel)
    {
        if ((currentWaterLevel + litres) > maxWaterLevel)
            currentWaterLevel = maxWaterLevel;
        else
            currentWaterLevel += litres;
    }
}

bool FireTruck::MaxWaterFilled()
{
    bool isTankFull = false;
    if (currentWaterLevel == maxWaterLevel)
        isTankFull = true;
    return isTankFull;
}

double FireTruck::getCurrentWaterLevel()
{
    return currentWaterLevel;
}

double FireTruck::getMaxWater()
{
    return maxWaterLevel;
}

void FireTruck::setHoseMoneyMulti(double multi) {
    (*this).hose.setMoneyMulti(multi);
}

void FireTruck::setHoseWaterMulti(double multi) {
    (*this).hose.setWaterMulti(multi);
}

double FireTruck::getHoseMoneyMulti() {
    return (*this).hose.getMoneyMulti();
}

double FireTruck::getHoseWaterMulti() {
    return (*this).hose.getWaterMulti();
}