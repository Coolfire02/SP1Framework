#pragma once
#include "GameObject.h"
#include "Item.h"

class ShopItem : public GameObject 
{
private:
	Item item;
	double cost;
public:
	ShopItem(Item, double);
	~ShopItem();

	void setCost(double);
	Item getItem();
	double getCost();

	std::string getType();
	ShopItem* clone() const { return new ShopItem(*this); };
};

