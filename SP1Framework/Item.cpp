#include "Item.h"

Item::Item(enum ITEMTYPE type, int amt, std::string displayName) : type(type), stack(amt), displayName(displayName) {

}

Item::Item(enum ITEMTYPE type, std::string displayName) : type(type), stack(1), displayName(displayName) {

}

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

enum ITEMTYPE Item::getItemType() {
    return type;
}