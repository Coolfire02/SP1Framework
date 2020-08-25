#pragma once
class Money
{
protected:
	int MoneyCount;

public:
	Money();
	~Money();
	int setMoney(int);
	bool spendMoney(int price);
	void receiveMoney(int amt);
	int getMoney();

};

