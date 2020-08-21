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
	HORIZONTAL_ROAD_ART,
	VERTICAL_ROAD_ART,
	FIRE_STATION_ART,
	RESERVOIR_ART,
	FOREST_ART,
	MINIGAME_WREST_ART, //Restaurant

	MINIGAME_CFT_ART, //Cat from Tree
	MINIGAME_CFT_CAT_ART,
	MINIGAME_CFT_TREE_ART,

	MINIGAME_CE_ART, //Charity Event
	MINIGAME_PCE_ART, //Promote Charity Event

	MINIGAME_RM_ART, //Raining Money
	MINIGAME_RM_COIN_ART,
	MINIGAME_RM_JAR_ART,

	MINIGAME_WL_ART, //Water Leakage
	MINIGAME_WFAR_ART, //Water from Reservoir
	MINIGAME_RW_ART, //Collect Rain Water
	MINIGAME_BHOS_ART, //Bee Hive Removal
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