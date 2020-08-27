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

class Item : public GameObject
{
private:
	const ITEMTYPE type;
	std::string displayName;
	int stack;
public:
	Item(ITEMTYPE, std::string);
	Item(ITEMTYPE, int, std::string);
	~Item();

	ITEMTYPE getItemType() const;
	void setDisplayName(std::string);
	std::string getDisplayName() const;
	void setAmount(int);

	std::string getType();
	Item* clone() const { return new Item(*this); };
};

