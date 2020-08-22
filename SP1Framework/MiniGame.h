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

class MiniGame : public GameObject
{
private:
	Console associatedConsole;
	LEVEL associatedLevel;
	Map MiniGameMap;
	int WaterCollected, MoneyEarned;
protected:
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

	COORD mapSize;
	ASCII MGascii;
	std::vector<GameObject*> mg_obj_ptr;
	void setWaterCollected(int w); //To set amount of Water collected in minigame
	void setMoneyEarned(int m); //To set amount of Money Earned in minigame
public:

	void renderMap();
	void renderObjsToMap(int gameType);


	bool CompletionCheck();  //To check whether the game is completed
	int getWaterCollected(); //Returns the amount of Water Collected in minigame
	int getMoneyEarned();  //Returns the amount of Money Earned in minigame
	COORD getMapSize();
	
	MiniGame(LEVEL level, Console& console);
	~MiniGame();

	virtual bool processKBEvents(SKeyEvent[]) = 0;
	virtual bool processMouseEvents(SMouseEvent&) = 0;
	virtual enum LEVELSTATE getAssociatedLSState() = 0;
	virtual std::string getType() = 0;
};
