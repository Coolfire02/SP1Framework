#pragma once
#include "GameObject.h"

enum ITEMTYPE {
	ABILITY_ZOOM,
	ABILITY_ROADREPAIR,
	ABILITY_HOMEBASE,
	ABILITY_MGRESET,
	HOSE_HOLY_WATER,
	HOSE_MONEY_SALVAGER,
	HOSE_ABSORBER,
	HOSE_MAGICAL_WATER,
	HOSE_MONEY_DUPLICATOR,
};

class Item
{
private:
	const ITEMTYPE type;
	int stack;
	Item(ITEMTYPE);
	Item(ITEMTYPE, int);
	~Item();

	void setAmount(int);

	std::string getType();
	ITEMTYPE getItemType();
	Item* clone() const { return new Item(*this); };
};

