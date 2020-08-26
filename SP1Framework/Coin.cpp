#include "Coin.h"

std::string Coin::getType()
{
	if (type == C_COIN)
		return "Coin";
	else if(type == C_BIGCOIN)
		return "Big_Coin";
	else
		return "Red_Coin";
}

int Coin::getCoinWorth()
{
	return CoinWorth;
}

Coin::Coin()
{
	type = C_COIN;
	art.setArt(COIN_ART);
	weight = 700;
	CoinWorth = 1;
}

Coin::Coin(enum COINTYPE type)
{ 
	(*this).type = type;
	weight = 700;
	if (type == C_COIN)
	{
		art.setArt(COIN_ART);
		CoinWorth = 1;
	}
	else if(type == C_BIGCOIN)
	{
		art.setArt(BIG_COIN_ART);
		CoinWorth = 6;
	}
	else
	{
		art.setArt(RED_COIN_ART);
		CoinWorth = -2;
	}
}

Coin::~Coin()
{
	//Intentionally left blank
}
