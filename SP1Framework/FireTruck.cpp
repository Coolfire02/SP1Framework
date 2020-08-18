#include "FireTruck.h"

FireTruck::FireTruck()
{
    art = ASCII(ARTTYPE::FIRE_TRUCK);
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
