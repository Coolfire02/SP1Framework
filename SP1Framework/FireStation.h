#pragma once
#include "GameObject.h"

class FireStation : public GameObject
{
public:
	FireStation();
	~FireStation();
	std::string getType();

	FireStation* clone() const { return new FireStation(*this); };
};

