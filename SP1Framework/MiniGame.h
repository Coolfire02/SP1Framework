#pragma once
#include "GameObject.h"
#include <string>

class MiniGame : public GameObject
{
public:
	virtual void WaterCollected(int);
	virtual void ManyReceived(int);
	virtual void UpdateMinigamewithKeyFunctions();
	virtual std::string getType() = 0;
};
