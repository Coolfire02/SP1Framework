#include "Player.h"

Player::Player()
{
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

std::string Player::getType() {
    return "FireMan";
}
