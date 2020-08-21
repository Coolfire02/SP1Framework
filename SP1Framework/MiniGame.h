#pragma once
#include "GameObject.h"
#include <string>
#include "ASCII.h"
#include "LevelState.h"

class MiniGame : public GameObject
{
protected:
	COORD mapSize;
	ASCII MGascii;
public:
	virtual void WaterCollected(int);
	virtual void ManyReceived(int);
	virtual void UpdateMinigamewithKeyFunctions();
	virtual enum LEVELSTATE getAssociatedLSState() = 0;
	virtual std::string getType() = 0;
	COORD getMapSize();
	
	MiniGame();
};
