#pragma once

#include "Framework/console.h"
#include "global.h"
#include "game.h"
#include "GameObject.h"
#include "ArtObject.h"
#include "FireTruck.h"
#include "FireStation.h"
#include "ShopItem.h"
#include "Forest.h"
#include "ASCII.h"
#include "Player.h"
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

//todo Map array consisting of all the different maps the level will use 
//have like a getMap from text folder esque thing for the begin scene, main menu etc etc
//when redering game, depending on the LS_STATE of the game a different map will be rendered
//when a keyboard input is hit into LEVEL class, it checks level state; which level state will run what
//function etc. If for e.g. in cut scene, no function is called. If in minigame, minigame move function
//will be called 

//Minigame class with a getMinigameType() so that when we iterate obj_ptr for minigames, easily identifiable
//minigame types then call functions like runkeyboardfunction(keyboardinput) on the specific and correct
//minigames identified using that getminigametype() function

//All cut scenes and minigames must have a map. A handler for them, so maybe for cut scenes we can have
//classes for each cut scene to handle animation. (similar to how minigames have their own handling of the map)
//Maybe each map can also be represented by a LS_STATE where LS_STATES are in direct relation to specific classes
//So that each map can be identifiable to be sent for checking depending on the state of the game to the
//said specific class.

//Can also have a level editor class, or maybe shov it in level class for easiness sake. Has its own map which
//will be a direct retrieve of the fresh level map from the text file (loading time expected)...
//when it switches to the level editor map, u will be when u hit mouse button, triggers a listener from game.cpp
//listened in level.cpp, if gamestate is level editor, iterate through all obj_ptrs to find if any is at the location
//being pressed, if so, var to lock in which obj_ptr it is that u are holding. 
//as you move your mouse the var world position will be updated
// keyboard handler from game.cpp listener will be listened in level.cpp class, if ls_state is in level editor
// it will allow u to move wasd to move the map's displayorigin (top left of buffer)

// render function in level class to redener the specific map chosen based on LS_State, u'd get the map
// iterate through till u find the displayorigin (top left of buffer) start writing into the buffer
// to get the map displayed on the screen.

class Level
{
private:
	Console associatedConsole;
	LEVEL level;
	LEVEL nextLevel;
	LEVELSTATE originalState;
	LEVELSTATE state;
	std::string levelName;

	Player* player_ptr;
	FireTruck* truck_ptr;
	MiniGame* currently_played_MG_ptr;
	CutScene* currently_played_CS_ptr;


	Text* Money_ptr;
	ProgressBar* ft_waterCollected;
	ProgressBar* level_progress;
	Text* ft_waterCollected_text;
	Text* level_progress_text;

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
	
	double fire;
	const double originalTotalFire;

	void newStageinit();
	void saveLevel();

	std::string getTruckWaterPrefix();
	std::string getFireRemainingPrefix();
	std::string getMoneyBalancePrefix();
	void updateProgressDisplays();
	void updateInventoryDisplays();

	void centralizeMapToTruck(Map* map);
public:
	void gameLoopListener();
	Level(LEVEL, Console&);
	~Level();
	bool setState(LEVELSTATE);
	enum LEVELSTATE getState();
	LEVEL getLevel();
	LEVEL getNextLevel();
	void resetNextLevel();
	void checkStateChange();
	void renderMap();
	void renderObjsToMap();
	bool processKBEvents(SKeyEvent[]);
	bool processMouseEvents(SMouseEvent&);

	void StartLevel();
};



