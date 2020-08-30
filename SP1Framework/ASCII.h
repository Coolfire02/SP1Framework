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
	WILDFIRE_TITLE_ART,

	FIRE_TRUCK_ART,
	FIRE_TRUCK_LEFT_ART,
	FIREFIGHTER_ART,
	FIRE_STATION_ART,
	RESERVOIR_ART,
	FOREST_ART,

	ABILITY_FIXROAD_ART,
	ABILITY_HOMEBASE_ART,
	ABILITY_ZOOM_ART,

	HOSE_ABSORBER_ART,
	HOSE_HOLYWATER_ART,
	HOSE_MAGICALWATER_ART,
	HOSE_MONEYDUPLICATOR_ART,
	HOSE_MONEYSALVAGER_ART,

	HORIZONTAL_ROAD_ART,
	HORIZONTAL_ROAD_SHORT_ART,
	HORIZONTAL_ROAD_BREAK_ART,
	VERTICAL_ROAD_ART,
	VERTICAL_ROAD_SHORT_ART,
	VERTICAL_ROAD_BREAK_ART,
	L_ROAD_ART, //L turn
	RL_ROAD_ART, //Right L turn
	LUL_ROAD_ART,//Left Up L turn
	RUL_ROAD_ART,//Right Up L turn
	DT_ROAD_ART,//Down T turns
	UT_ROAD_ART,//Up T turns
	LVT_ROAD_ART,//Left Vertical T turns
	RVT_ROAD_ART,//Right Vertical T turns
	X_ROAD_ART,//Crossroad

	SHOP_ART,

	MINIGAME_WREST_ART, //Restaurant

	MINIGAME_CFT_ART, //Cat from Tree
	CAT_ART,
	TREE_ART,

	MINIGAME_CE_ART, //Charity Event
	MINIGAME_PCE_ART, //Promote Charity Event

	MINIGAME_RM_ART, //Raining Money
	RED_COIN_ART,
	BIG_COIN_ART,
	COIN_ART,
	JAR_ART,

	MINIGAME_WL_ART, //Water Leakage
	PIPE_ART,
	WRENCH_HEAD_ART,
	WRENCH_TAIL_ART,
	BUCKET_ART,

	MINIGAME_WFAR_ART, //Water from Reservoir

	MINIGAME_RW_ART, //Collect Rain Water
	DROPLET_ART,
	BOTTLE_ART,
	HAIL_ART,

	MINIGAME_BHOS_ART, //Bee Hive Removal
	BEEHIVE_ART,
	BEEHIVE_ICON_ART,

	W_ART,
	A_ART,
	S_ART,
	D_ART,

	POLE_ART,

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
	
	void setArt(ARTTYPE type);
	bool setArt(BAR barType, short width, short height, WORD border, WORD fill, double progress);
	bool setArt(std::string txt);
	bool setArt(std::string txt, WORD bg);

	bool setArt(int width, int height, WORD bg, WORD border);

	void deleteArt();
	ASCII(ARTTYPE);
	ASCII();
	~ASCII();
};