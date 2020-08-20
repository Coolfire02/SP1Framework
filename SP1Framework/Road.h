#pragma once
#include "GameObject.h"

class Road : public GameObject
{
public:
	Road();
	~Road();
	std::string getType();
};

