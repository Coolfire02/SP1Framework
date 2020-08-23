#include "Bank.h"

Bank::Bank()
{
	art.setArt(BANK_ART);
	weight = 1000;
}

Bank::~Bank()
{
	//Intentionally left blank.
}

std::string Bank::getType()
{
	return "Bank";
}
