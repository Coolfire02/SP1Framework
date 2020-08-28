#pragma once
#include "GameObject.h"

enum ROADTYPE
{
	R_HORIZONTAL,
	R_VERTICAL,
	R_L, //L turn
	R_RL, //Right L turn
	R_LUL,//Left Up L turn
	R_RUL,//Right Up L turn
	R_DT,//Down T turns
	R_UT,//Up T turns
	R_LVT,//Left Vertical T turns
	R_RVT,//Right Vertical T turns
	R_X, //CrossRoad
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
	void setRoadType(ROADTYPE);
	ROADTYPE getRoadType();
	void rotateRoadType();

	Road* clone() const { return new Road(*this); };
};

