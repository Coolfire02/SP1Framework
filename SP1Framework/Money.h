#pragma once
class Money
{
protected:
	double MoneyCount;

public:
	Money();
	~Money();
	int setMoney(int);
	bool spendMoney(int price);
	void receiveMoney(double amt);
	double getMoney();

};

