#pragma once

#include "GameObject.h"
#include"Position.h"
#include"Hose.h"
#include"ASCII.h"

class FireTruck : public GameObject
{
private:
	Position FTpos1;
	Hose H1;
	ASCII FTasc1;
public:
	FireTruck();
	~FireTruck();
	int WaterFilled(int);
	int MaxWaterFilled(int);

};

