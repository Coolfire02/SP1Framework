#pragma once
#include"Position.h"

class ProgressBar
{
private:
	int FillColour, BorderColour, Width, Length;
	Position PBpos1;
public:
	ProgressBar();
	~ProgressBar();
};

