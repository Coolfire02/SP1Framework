#include "Hose.h"

Hose::Hose() : waterMultiplier(1), moneyMultiplier(1)
{
}

Hose::~Hose()
{
}

void Hose::setMoneyMulti(double multi) {
	if (multi > 0) {
		moneyMultiplier = multi;
	}
}

void Hose::setWaterMulti(double multi) {
	if (multi > 0) {
		waterMultiplier = multi;
	}
}

double Hose::getMoneyMulti() {
	return moneyMultiplier;
}

double Hose::getWaterMulti() {
	return waterMultiplier;
}


