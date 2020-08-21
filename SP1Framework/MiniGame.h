#pragma once
#include "GameObject.h"
#include "global.h"
#include <string>
#include "ASCII.h"
#include "Level.h"
#include "LevelState.h"
#include "Map.h"

class MiniGame : public GameObject
{
private:
	Console associatedConsole;
	LEVEL associatedLevel;
	Map MiniGameMap;
	int WaterCollected, MoneyEarned;
	bool Completed;
protected:
	COORD mapSize;
	ASCII MGascii;
	std::vector<GameObject*> mg_obj_ptr;
	void setWaterCollected(int w); //To set amount of Water collected in minigame
	void setMoneyEarned(int m); //To set amount of Money Earned in minigame
public:
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

	void renderMap();
	void renderObjsToMap(int gameType);
	bool processKBEvents(SKeyEvent[]);
	bool processMouseEvents(SMouseEvent&);


	bool CompletionCheck();  //To check whether the game is completed
	int getWaterCollected(); //Returns the amount of Water Collected in minigame
	int getMoneyEarned();  //Returns the amount of Money Earned in minigame
	virtual void UpdateMinigamewithKeyFunctions();
	virtual enum LEVELSTATE getAssociatedLSState() = 0;
	virtual std::string getType() = 0;
	COORD getMapSize();
	
	MiniGame(LEVEL level, Console& console);
	~MiniGame();
};
