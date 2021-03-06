#pragma once

#include "GameObject.h"
#include "ProgressBar.h"
#include "Position.h"
#include "Money.h"
#include "ASCII.h"
#include "Inventory.h"

class Player : public GameObject
{
private:
	Inventory inventory;
	std::string getType();
	Money M1;
public:
	Player();
	~Player();
	int TaskCompleteCount(int);
	bool PlayerInFT();

	bool spendMoney(int price);
	void receiveMoney(double amt);
	double getMoney();

	Inventory& getInventory();

	Player* clone() const { return new Player(*this); };
};

