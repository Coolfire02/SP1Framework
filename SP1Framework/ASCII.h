#pragma once
#include "global.h"
#include <Windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

enum ARTTYPE
{
	FIRE_TRUCK_ART,
	FIREFIGHTER_ART,
	FIRE_STATION_ART,
	RESERVOIR_ART,
	FOREST_ART,
	MINIGAME_WREST_ART,
	MINIGAME_CFT_ART,
	MINIGAME_CE_ART,
	MINIGAME_PCE_ART,
	MINIGAME_GF_ART,
	MINIGAME_WL_ART,
	MINIGAME_WFAR_ART,
	MINIGAME_RW_ART,
	MINIGAME_BHOS_ART,
	DEFAULT_ART
};

class ASCII
{
private:
	unsigned int xLength;
	unsigned int yLength;
	CHAR_INFO** art;
	void tokenize(std::string const& str, const char delim, std::vector<std::string>& out);
protected:
	CHAR_INFO** getArt();
public:
	unsigned int getXLength();
	unsigned int getYLength();
	CHAR_INFO getArtAtLoc(COORD);
	
	bool setArt(ARTTYPE);
	ASCII(ARTTYPE);
	ASCII();
	~ASCII();
};