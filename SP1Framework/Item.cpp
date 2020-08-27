#include "Item.h"

Item::Item(ITEMTYPE type, int amt, std::string displayName) : type(type), stack(amt), displayName(displayName) {}
Item::Item(ITEMTYPE type, std::string displayName) : type(type), displayName(displayName) {}
Item::~Item() {};

void Item::setAmount(int amt) {
	stack = amt;
}

void Item::setDisplayName(std::string name) {
	displayName = name;
}

std::string Item::getDisplayName() const {
	return displayName;
}

ITEMTYPE Item::getItemType() const {
	return type;
}

std::string Item::getType() {
	return "Item";
}
