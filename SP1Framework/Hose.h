#pragma once
class Hose
{
private:
	double waterMultiplier;
	double moneyMultiplier;
public:
	Hose();
	~Hose();
	
	void setMoneyMulti(double);
	void setWaterMulti(double);
	double getMoneyMulti();
	double getWaterMulti();
};

