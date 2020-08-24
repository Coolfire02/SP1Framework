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

int Money::Getmoney(int)
{
	return MoneyCount;
}

int Money::Setmoney(int)
{
	return 0;
}
bool Money::Spend(int price)
{
	if (MoneyCount < price)
		/*cout << "Not enough Money" << endl;*/
		return false;// not enough money
	MoneyCount -= price;
	return true;
}

void Money::Receive(int amt)
{
	MoneyCount += amt;
}

void Money::ShowMoney()
{
	
}
