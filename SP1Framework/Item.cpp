#include "Item.h"

Item::Item(ITEMTYPE type, int amt) : type(type), stack(amt) {}
Item::Item(ITEMTYPE type) : type(type) {}
Item::~Item() {};

void Item::setAmount(int amt) {
	stack = amt;
}

ITEMTYPE Item::getItemType() {
	return type;
}

std::string Item::getType() {
	return "Item";
}
