#pragma once
#include "GameObject.h"
class Bank :
    public GameObject
{
public:
	Bank();
	~Bank();
	std::string getType();
};

