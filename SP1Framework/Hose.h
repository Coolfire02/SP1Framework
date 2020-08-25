#pragma once
class Hose
{
private:
	int WaterCollectionMultiplier, WaterSpreadSpeed, UpgradeCost;
public:
	Hose();
	~Hose();
	void UpgradeHost(int muliplier);

	Hose* clone() const { return new Hose(*this); };
};

