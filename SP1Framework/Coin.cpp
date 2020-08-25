#include "Coin.h"

std::string Coin::getType()
{
	return "Coin";
}

int Coin::getCoinWorth()
{
	return CoinWorth;
}

Coin::Coin()
{
	art.setArt(COIN_ART);
	weight = 700;
	CoinWorth = 1;
}

Coin::~Coin()
{
	//Intentionally left blank
}
