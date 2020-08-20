#pragma once
#include "GameObject.h"

class Road : public GameObject
{
private:
	enum ROADTYPE
	{
		HORIZONTAL,
		VERTICAL
	};
public:
	Road();
	Road(ROADTYPE);
	~Road();
	std::string getType();
};

