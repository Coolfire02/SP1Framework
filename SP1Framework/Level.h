#pragma once

#include "Framework/console.h"
#include "global.h"
#include "game.h"
#include "GameObject.h"
#include "ArtObject.h"
#include "FireTruck.h"
#include "FireStation.h"
#include "Player.h"
#include "Item.h"
#include "ShopItem.h"
#include "Forest.h"
#include "ASCII.h"
#include "MiniGame.h"
#include "Map.h"
#include "Stage.h"
#include "MiniGame_RM.h"
#include "MiniGame_WL.h"
#include "MiniGame_BHOS.h"
#include "MiniGame_RW.h"
#include "MiniGame_CFT.h"
#include "Road.h"
#include "LevelState.h"
#include "CutScene.h"
#include "StartScene.h"

#include <vector>
#include <unordered_map>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>

class Level
{
private:
	Console associatedConsole;
	LEVEL level;
	LEVEL nextLevel;
	LEVELSTATE originalState;
	LEVELSTATE state;
	std::string levelName;
	bool completed;

	Text* win;
	Player* player_ptr;
	FireTruck* truck_ptr;
	MiniGame* currently_played_MG_ptr;
	CutScene* currently_played_CS_ptr;

	Text* Money_ptr;
	ProgressBar* ft_waterCollected;
	ProgressBar* level_progress;
	Text* ft_waterCollected_text;
	Text* level_progress_text;
	Text* topOfScreenTXT;

	std::vector<MiniGame*> mg_ptr;
	std::vector<GameObject*> obj_ptr;
	std::vector<CutScene*> cs_ptr;
	std::vector<Stage*> stages_ptr;
	std::vector<LEVELSTATE> levelStates;
	std::unordered_map<LEVELSTATE, Map* > levelspecific_maps;
	
	// shop variables
	std::vector<GameObject*> shop_obj_ptr;

	// power up variables
	double PU_zoom_timer;
	double PU_homebase_timer;
	ArtObject* PU_zoom;
	ArtObject* PU_road_repair;
	ArtObject* PU_homebase;
	Text* PU_zoom_inven_display;
	Text* PU_road_repair_inven_display;
	Text* PU_homebase_inven_display;

	bool devMode = true;
	GameObject* pickedUp_obj;
	
	const double originalTotalFire;
	double fire;

	void newStageinit();
	void saveLevel();

	std::string getTruckWaterPrefix();
	std::string getFireRemainingPrefix();
	std::string getMoneyBalancePrefix();
	void updateProgressDisplays();
	void updateInventoryDisplays();

	void centralizeMapToTruck(Map* map);
public:
	bool isComplete();
	void gameLoopListener();
	Level(LEVEL, Console&);
	~Level();
	bool setState(LEVELSTATE);
	enum LEVELSTATE getState();
	LEVEL getLevel();
	LEVEL getNextLevel();
	void resetNextLevel();
	void checkStateChange();
	bool renderMap();
	bool renderObjsToMap();
	bool processKBEvents(SKeyEvent[]);
	bool processMouseEvents(SMouseEvent&);
	void setTopOfScreenTXT(std::string txt);
	void StartLevel();
};



