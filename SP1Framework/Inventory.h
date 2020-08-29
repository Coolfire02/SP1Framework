#pragma once
#include "Item.h"

class Inventory
{
private:
	std::vector<Item> items;
public:
	Inventory();
	~Inventory();
	void addItem(Item);
	bool removeItem(Item);
	std::vector<Item>& getItems();
	bool contains(Item);
	int getAmountOfType(ITEMTYPE);
};

