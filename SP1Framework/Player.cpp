#include "Player.h"

Player::Player()
{
    art.setArt(FIREFIGHTER_ART);
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
    return "Player";
}
