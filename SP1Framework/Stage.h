#pragma once
#include "GameObject.h"

class Stage : public GameObject
{
private:
	LEVEL stage;
public:
	Stage(LEVEL);
	~Stage();
	std::string getType();
	LEVEL getStage();
	Stage* clone() const { return new Stage(*this); };
};
