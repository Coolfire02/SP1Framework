#pragma once
#ifndef ITEM_H
#define ITEM_H

#include "global.h"
#include <string>

class Item
{
private:
    ITEMTYPE type;
    std::string displayName;
    int stack;
public:

    Item(enum ITEMTYPE, int, std::string);
    Item(enum ITEMTYPE, std::string);

    enum ITEMTYPE getItemType();
    void setDisplayName(std::string);
    std::string getDisplayName();
    void setAmount(int);
    int getAmount();

    Item* clone() const { return new Item(*this); };
};


#endif