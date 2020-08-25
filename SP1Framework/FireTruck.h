#pragma once

#include "GameObject.h"
#include"Hose.h"

class FireTruck : public GameObject
{
private:
	double currentWaterLevel;
	double maxWaterLevel;
	Hose H1;
public:
	FireTruck(double maxWater);
	~FireTruck();
	std::string getType();
	void setMaxWaterLevel(double map);
	void FillWater(double);
	bool MaxWaterFilled();
	double getCurrentWaterLevel();
	double getMaxWater();
	void setWaterLevel(double);
};

