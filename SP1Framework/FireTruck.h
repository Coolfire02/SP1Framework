#pragma once

#include "GameObject.h"
#include"Position.h"
#include"Hose.h"

class FireTruck : public GameObject
{
private:
	Position FTpos1;
	Hose H1;
public:
	FireTruck();
	~FireTruck();
	std::string getType();
	int WaterFilled(int);
	int MaxWaterFilled(int);

};

