#pragma once
#include "GameObject.h"

class Item : public GameObject
{
private:
	ITEMTYPE type;
	std::string displayName;
	int stack;
public:
	Item(ITEMTYPE, std::string);
	Item(ITEMTYPE, int, std::string);
	~Item();

	ITEMTYPE getItemType();
	void setDisplayName(std::string);
	std::string getDisplayName();
	void setAmount(int);
	int getAmount();

	std::string getType();
	Item* clone() const { return new Item(*this); };
};

