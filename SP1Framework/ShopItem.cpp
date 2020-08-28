#include "ShopItem.h"

ShopItem::ShopItem(Item item, double cost) : item(item), cost(cost) {
	switch (item.getItemType()) {
	case ABILITY_ZOOM:
		art.setArt(10, 5, 0x80, 0xA0);
	default:
		art.setArt(10, 5, 0xF0, 0xF0);
	}
}
ShopItem::~ShopItem() {}

void ShopItem::setCost(double cost) {
	(*this).cost = cost;
}

double ShopItem::getCost() {
	return cost;
}

Item ShopItem::getItem() {
	return item;
}

std::string ShopItem::getType() {
	return "ShopItem";
}