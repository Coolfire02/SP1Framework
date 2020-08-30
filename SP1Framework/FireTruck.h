#pragma once

#include "GameObject.h"
#include"Hose.h"

enum TRUCK_DIRECTION {
	T_LEFT,
	T_RIGHT
};

class FireTruck : public GameObject
{
private:
	double currentWaterLevel;
	double maxWaterLevel;
	Hose hose;
	TRUCK_DIRECTION direction;
public:
	FireTruck(double maxWater);
	~FireTruck();
	void setDirection(TRUCK_DIRECTION);
	std::string getType();
	void setMaxWaterLevel(double map);
	void FillWater(double);
	bool MaxWaterFilled();
	double getCurrentWaterLevel();
	double getMaxWater();
	void setWaterLevel(double);

	void setHoseMoneyMulti(double);
	void setHoseWaterMulti(double);
	double getHoseMoneyMulti();
	double getHoseWaterMulti();

	FireTruck* clone() const { return new FireTruck(*this); };
};

