#include "Hose.h"

Hose::Hose()
{
	WaterCollectionMultiplier = 1;
	WaterSpreadSpeed = 25;
	UpgradeCost = 250;
}

Hose::~Hose()
{
}

void Hose::UpgradeHost(int muliplier)
{
	for (int muliplier = 1; muliplier < 9; muliplier++)
	{
		WaterCollectionMultiplier = muliplier;
		WaterSpreadSpeed += 25;
		UpgradeCost += 100;
	}
}
