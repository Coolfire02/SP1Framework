#include "Inventory.h"

Inventory::Inventory() {

}

Inventory::~Inventory() {

}

void Inventory::addItem(Item item) {
	for (auto& loopItem : items) {
		if (loopItem.getItemType() == item.getItemType()) {
			loopItem.setAmount(loopItem.getAmount() + item.getAmount());
			return;
		}
	}
	(*this).items.push_back(item);
}

std::vector<Item>& Inventory::getItems() {
	return items;
}

bool Inventory::contains(Item item) {
	for (auto& loopItem : items) {
		if (loopItem.getItemType() == item.getItemType()) {
			if (loopItem.getAmount() >= item.getAmount())
				return true;
		}
	}
	return false;
}

bool Inventory::removeItem(Item item) {
	bool removed = false;
	for (auto it = items.begin(); it != items.end(); /*NOTHING*/) {
		if ((*it).getItemType() == item.getItemType()) {
			if ((*it).getAmount() >= item.getAmount()) {
				removed = true;
				(*it).setAmount((*it).getAmount() - item.getAmount());
				if ((*it).getAmount() <= 0) {
					it = items.erase(it);
				}
				else {
					++it;
				}
			}
			else {
				++it;
			}
		}
		else {
			++it;
		}
	}
	return removed;
}