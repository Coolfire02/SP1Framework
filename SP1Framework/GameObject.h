#pragma once
#include <Windows.h>
#include "ASCII.h"

class GameObject
{

private:
	ASCII art;
	COORD worldPosition;
public:
	GameObject();
	~GameObject();

	bool isCollided(GameObject&);

	CHAR_INFO** getArt();
	COORD getWorldPosition();
	unsigned int getXLength();
	unsigned int getYLength();

	bool setWorldPosition(COORD);
	bool setWorldPosition(unsigned int, unsigned int);

};

