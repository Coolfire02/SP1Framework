#pragma once
#include "Player.h"
#include "Framework/console.h"
#include "GameObject.h"
#include "global.h"
#include <string>
#include "ASCII.h"
#include "LevelState.h"
#include "Map.h"
#include <map>
#include <vector>
#include <time.h>

class MiniGame : public GameObject
{
private:
	LEVEL associatedLevel;
protected:
	Console associatedConsole;
	Map MiniGameMap;
	int WaterCollected, MoneyEarned;

	bool Completed;
	Player* player_ptr;
	enum MiniGames
	{
		MINIGAME_WREST, //Restaurant
		MINIGAME_CFT, //Cat from Tree
		MINIGAME_CE, //Charity Event
		MINIGAME_PCE, //Promote Charity Event
		MINIGAME_RM, //Raining Money
		MINIGAME_WL, //Water Leakage
		MINIGAME_WFAR, //Water from Reservoir
		MINIGAME_RW, //Collect Rain Water
		MINIGAME_BHOS, //Bee Hive Removal
	};
	ASCII MGascii;
	std::vector<GameObject*> mg_obj_ptr;
	void setWaterCollected(int w); //To set amount of Water collected in minigame
	void setMoneyEarned(int m); //To set amount of Money Earned in minigame
public:

	void renderObjsToMap();
	void renderMap();

	bool isCompleted();  //To check whether the game is completed
	int getWaterCollected(); //Returns the amount of Water Collected in minigame
	int getMoneyEarned();  //Returns the amount of Money Earned in minigame
	COORD getMapSize();
	
	MiniGame(LEVEL level, Console& console);
	~MiniGame();

	virtual void gameLoopListener() = 0;
	virtual bool processKBEvents(SKeyEvent[]) = 0;
	virtual bool processMouseEvents(SMouseEvent&) = 0;
	virtual enum LEVELSTATE getAssociatedLSState() = 0;
	virtual std::string getType() = 0;
};
