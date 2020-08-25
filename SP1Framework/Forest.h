#pragma once
#include "GameObject.h"

class Forest : public GameObject
{
public:
	Forest();
	~Forest();
	std::string getType();

	Forest* clone() const { return new Forest(*this); };
};

