#include "Money.h"
#include<iostream>

Money::Money()
{
	MoneyCount = 0;
}


Money::~Money()
{
	//Intentionally left blank.
}


int Money::setMoney(int)
{
	return 0;
}
bool Money::spendMoney(int price)
{
	if (MoneyCount < price)
		return false;// not enough money
	else
		MoneyCount -= price;
		return true;
}

void Money::receiveMoney(double amt)
{
	MoneyCount += amt;
}

double Money::getMoney()
{
	return MoneyCount;
}
