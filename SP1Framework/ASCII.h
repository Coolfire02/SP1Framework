#pragma once
#include <Windows.h>

enum ARTTYPE {
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
	DEFAULT
};

class ASCII
{
private:
	unsigned int xLength;
	unsigned int yLength;
	CHAR_INFO** art;
public:
	unsigned int getXLength();
	unsigned int getYLength();
	CHAR_INFO getArtAtLoc(COORD);
	bool setArt(ARTTYPE);
	ASCII(ARTTYPE);
	ASCII();
	~ASCII();
};