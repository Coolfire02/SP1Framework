#pragma once
using namespace std;
class Money
{
protected:
	int MoneyCount;

public:
	Money();
	~Money();
	int Getmoney(int);
	int Setmoney(int);
	bool Spend(int price);
	void Receive(int amt);
	void ShowMoney();

};

