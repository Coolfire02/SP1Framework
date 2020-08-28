#include "Item.h"

Item::Item(ITEMTYPE type, int amt, std::string displayName) : type(type), stack(amt), displayName(displayName) {}
Item::Item(ITEMTYPE type, std::string displayName) : type(type), stack(1), displayName(displayName) {}
Item::~Item() {};

void Item::setAmount(int amt) {
	stack = amt;
}

int Item::getAmount() {
	return stack;
}

void Item::setDisplayName(std::string name) {
	displayName = name;
}

std::string Item::getDisplayName() {
	return displayName;
}

ITEMTYPE Item::getItemType() {
	return type;
}

std::string Item::getType() {
	return "Item";
}
