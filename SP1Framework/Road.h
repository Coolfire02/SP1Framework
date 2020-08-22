#pragma once
#include "GameObject.h"

enum ROADTYPE
{
	R_HORIZONTAL,
	R_VERTICAL,
	R_COUNT
};

class Road : public GameObject
{
private:
	ROADTYPE type;
public:
	Road();
	Road(ROADTYPE);
	~Road();
	std::string getType();
};

