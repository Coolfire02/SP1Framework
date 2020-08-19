#pragma once
#include "GameObject.h"
#include "FireTruck.h"
#include "ASCII.h"
#include "Player.h"
#include "MiniGame.h"
#include "Map.h"

enum LEVEL {
	MAINMENU,
	TUTORIAL,
	STAGE_1_LEVEL_1,
	STAGE_2_LEVEL_1,
};

enum LEVELSTATE {
	LS_MAINMENU,
	LS_BEGIN_SCENE,
	LS_MAINGAME,
	LS_MINIGAME_WREST,
	LS_MINIGAME_CFT,
	LS_MINIGAME_CE,
	LS_MINIGAME_PCE,
	LS_MINIGAME_GF,
	LS_MINIGAME_WL,
	LS_MINIGAME_WFAR,
	LS_MINIGAME_RW,
	LS_MINIGAME_BHOS,
	LS_FOREST_SCENE,
	LS_END_SCENE,
	LS_LEVEL_BUILDER
};

class Level
{
private:
	LEVEL level;
	Player* player_ptr;
	FireTruck* truck_ptr;
	MiniGame* mg_ptr;
	LEVELSTATE state;
	
	COORD displayOrigin;
	bool playerInTruck = false;
	Map map;

	bool devMode = false;
	

public:
	Level(LEVEL);
	~Level();
};



