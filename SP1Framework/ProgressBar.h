#pragma once

#include "GameObject.h"
#include"Position.h"

class ProgressBar : public GameObject
{
private:
	int FillColour, BorderColour, Width, Length;
	std::string getType();
	Position PBpos1;
public:
	ProgressBar();
	~ProgressBar();
};

