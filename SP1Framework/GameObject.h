#pragma once
#include <Windows.h>
#include "ASCII.h"

class GameObject
{
protected:
	ASCII art;
	COORD worldPosition;
	bool setArt(CHAR_INFO**& art); //todo getArt func in ASCII, in construct of each child add a setArt
public:
	GameObject();
	~GameObject();

	bool isCollided(GameObject&);

	CHAR_INFO getArtAtLoc(COORD);
	COORD getWorldPosition();
	unsigned int getXLength();
	unsigned int getYLength();

	bool setWorldPosition(COORD);
	bool setWorldPosition(unsigned int, unsigned int);
};

