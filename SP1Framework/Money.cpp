#include "Money.h"
#include<iostream>
using namespace std;

Money::Money()
{
	MoneyCount = 0;
}


Money::~Money()
{
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
		cout << "Not enough Money" << endl;
		return false;// not enough money
	MoneyCount -= price;
	return true;
}

void Money::Receive(int amt)
{
	cout << "You Received: ";
	cout << amt << " dollars" << endl;
	MoneyCount += amt;

}

void Money::ShowMoney()
{
	cout << MoneyCount << endl;
}
