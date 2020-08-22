#pragma once

#include "GameObject.h"
#include"Hose.h"

class FireTruck : public GameObject
{
private:
	int currentWaterLevel;
	int MaxWaterLevel;
	Hose H1;
public:
	FireTruck();
	~FireTruck();
	std::string getType();
	void setMaxWaterLevel(int litres);
	void FillWater(int);
	bool MaxWaterFilled();
	int getCurrentWaterLevel();
};

