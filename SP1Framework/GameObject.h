#pragma once
#include <Windows.h>

class GameObject
{

private:
	int** objectCords_ptr;
	int objXLength, objYLength;
public:
	GameObject(int, int);
	~GameObject();
};

enum Object
{
    FIRE_TRUCK,
	FIREFIGHTER,
	RESERVOIR,
	FOREST,
	MINIGAME_WREST,
	MINIGAME_CFT,
	MINIGAME_CE,
	MINIGAME_PCE,
	MINIGAME_GF,
	MINIGAME_WL,
	MINIGAME_WFAR,
	MINIGAME_RW,
	MINIGAME_BHOS,
	OBJ_COUNT
};