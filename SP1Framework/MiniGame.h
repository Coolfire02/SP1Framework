#pragma once
#include "Player.h"
#include "Framework/console.h"
#include "GameObject.h"
#include "Text.h"
#include "global.h"
#include <string>
#include "ASCII.h"
#include "LevelState.h"
#include "Map.h"
#include <map>
#include <vector>
#include <time.h>
#include <list>

class MiniGame : public GameObject
{
private:
	LEVEL associatedLevel;
	double mg_start_time;
	bool mg_started;
	virtual void mgGameInit() = 0; // when start() is called, it'll call this for all MGs to read
protected:
	Console associatedConsole;
	Map MiniGameMap;
	int WaterCollected, MoneyEarned;

	bool Completed;
	bool isInInstructions;
	Player* player_ptr;
	Text* button_ptr;
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
	std::vector<GameObject*> instructions_obj_ptr;
	LEVEL getAssociatedLevel();
	void setWaterCollected(int w); //To set amount of Water collected in minigame
	void setMoneyEarned(int m); //To set amount of Money Earned in minigame
	double getStartTime();
	bool isStarted();

	virtual bool processKBEvents_mg(SKeyEvent[]) = 0;
	virtual bool processMouseEvents_mg(SMouseEvent&) = 0;
public:
	
	void renderObjsToMap();
	void renderMap();

	bool isCompleted();  //To check whether the game is completed
	void start();
	int getWaterCollected(); //Returns the amount of Water Collected in minigame
	int getMoneyEarned();  //Returns the amount of Money Earned in minigame
	COORD getMapSize();
	
	MiniGame(LEVEL level, Console& console);
	~MiniGame();

	virtual void gameLoopListener() = 0;

	virtual enum LEVELSTATE getAssociatedLSState() = 0;
	virtual std::string getType() = 0;
	bool processKBEvents(SKeyEvent[]);
	bool processMouseEvents(SMouseEvent&);
	virtual MiniGame* clone() const = 0;
};
