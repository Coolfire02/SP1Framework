#pragma once
#include <Windows.h>
#include "ASCII.h"
#include <string>

class GameObject
{
private:
	COORD worldPosition;
	bool interactable;
protected:
	ASCII art;
public:
	GameObject();
	~GameObject();

	bool isCollided(GameObject&);
	bool isInteractable();

	CHAR_INFO getArtAtLoc(COORD);
	COORD getWorldPosition();
	unsigned int getXLength();
	unsigned int getYLength();

	virtual std::string getType() = 0;

	void setInteractable(bool);
	bool setWorldPosition(COORD);
	bool setWorldPosition(unsigned int, unsigned int);
};

