#pragma once

#include "GameObject.h"

class ProgressBar : public GameObject
{
private:
	BAR barType;
	int max;
	double progress;
	int fillColour, borderColour, width, height;
	std::string getType();
	
public:
	ProgressBar(BAR barType, short width, short height, WORD border, WORD fill);
	ProgressBar(BAR barType, short width, short height);
	void updateBar();
	void setProgress(double);
	~ProgressBar();
	int getMax();
	ProgressBar* clone() const { return new ProgressBar(*this); };
};

