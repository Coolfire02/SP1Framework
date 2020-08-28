#include "ShopItem.h"

ShopItem::ShopItem(Item item, double cost) : item(item), cost(cost) {
	switch (item.getItemType()) {
	case ABILITY_ZOOM:
		art.setArt(ABILITY_ZOOM_ART);
		break;
	case ABILITY_HOMEBASE:
		art.setArt(ABILITY_HOMEBASE_ART);
		break;
	case ABILITY_UNLOCKMG:
		art.setArt(ABILITY_UNLOCKMG_ART);
		break;
	case ABILITY_ROADREPAIR:
		art.setArt(ABILITY_FIXROAD_ART);
		break;
	case HOSE_HOLY_WATER:
		art.setArt(HOSE_HOLYWATER_ART);
		break;
	case HOSE_ABSORBER:
		art.setArt(HOSE_ABSORBER_ART);
		break;
	case HOSE_MAGICAL_WATER:
		art.setArt(HOSE_MAGICALWATER_ART);
		break;
	case HOSE_MONEY_DUPLICATOR:
		art.setArt(HOSE_MONEYDUPLICATOR_ART);
		break;
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