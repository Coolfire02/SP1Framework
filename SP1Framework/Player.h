#pragma once

#include "GameObject.h"
#include"ProgressBar.h"
#include"Position.h"
#include"Money.h"
#include"ASCII.h"

class Player : public GameObject
{
private:
	std::string getType();
	Position Ppos1;
	Money M1;
	//ASCII Pasc1;
public:
	Player();
	~Player();
	int TaskCompleteCount(int);
	bool PlayerInFT();

	bool spendMoney(int price);
	void receiveMoney(int amt);
	int getMoney();

	Player* clone() const { return new Player(*this); };
};

