#pragma once

#include "GameObject.h"
#include"ProgressBar.h"
#include"Position.h"
#include"Money.h"
#include"ASCII.h"

using namespace std;

class Player : public GameObject
{
private:
	ProgressBar Bar1;
	Position Ppos1;
	Money M1;
	//ASCII Pasc1;
public:
	Player();
	~Player();
	int TaskCompleteCount(int);

};

