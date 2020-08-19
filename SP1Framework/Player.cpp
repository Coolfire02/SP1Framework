#include "Player.h"

Player::Player()
{
    art.setArt(FIREFIGHTER);
}

Player::~Player()
{
}

int Player::TaskCompleteCount(int)
{
    return 0;
}
