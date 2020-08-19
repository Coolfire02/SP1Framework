#include "FireTruck.h"

FireTruck::FireTruck()
{
    art.setArt(FIRE_TRUCK_ART);
}

FireTruck::~FireTruck()
{
}

int FireTruck::WaterFilled(int)
{
    return 0;
}

int FireTruck::MaxWaterFilled(int)
{
    return 0;
}

std::string FireTruck::getType() {
    return "FireTruck";
}