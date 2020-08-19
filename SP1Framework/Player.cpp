#include "Player.h"

Player::Player()
{

    art.setArt(FIREFIGHTER_ART);
}

Player::~Player()
{
}

int Player::TaskCompleteCount(int)
{
    return 0;
}

bool Player::PlayerInFT()
{
    return false;
}
