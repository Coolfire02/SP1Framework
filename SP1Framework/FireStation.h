#pragma once
#include "GameObject.h"

class FireStation : public GameObject
{
public:
	FireStation();
	~FireStation();
	std::string getType();
};

