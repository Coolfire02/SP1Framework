#pragma once

#include "GameObject.h"
#include"Hose.h"

class FireTruck : public GameObject
{
private:
	Hose H1;
public:
	FireTruck();
	~FireTruck();
	std::string getType();
	int WaterFilled(int);
	int MaxWaterFilled(int);

};

