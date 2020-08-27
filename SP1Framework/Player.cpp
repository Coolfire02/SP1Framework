#include "Player.h"

Player::Player()
{
    M1.setMoney(0);
    art.setArt(FIREFIGHTER_ART);
    weight = 800;
}

Player::~Player()
{
    // intentionally left blank
}

int Player::TaskCompleteCount(int)
{
    return 0;
}

bool Player::PlayerInFT()
{
    return false;
}

bool Player::spendMoney(int price)
{
    return M1.spendMoney(price);
}

void Player::receiveMoney(int amt)
{
    M1.receiveMoney(amt);
}

int Player::getMoney()
{
    return M1.getMoney();
}

std::string Player::getType() {
    return "FireMan";
}

Inventory& Player::getInventory() {
    return inventory;
}


