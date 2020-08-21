#pragma once
#include <Windows.h>
#include "ASCII.h"
#include <string>

class GameObject
{
private:
	COORD worldPosition;
	bool interactable;
	bool active;
protected:
	ASCII art;
	short weight; // > weight = > priority
public:
	GameObject();
	~GameObject();

	bool isCollided(GameObject&);
	bool isInteractable();

	CHAR_INFO getArtAtLoc(COORD);
	CHAR_INFO getArtAtLoc(int,int);
	COORD getWorldPosition();
	short getWeight();
	unsigned int getXLength();
	unsigned int getYLength();
	bool isActive();
	bool isInLocation(COORD);
	bool isInLocation(int, int);

	virtual std::string getType() = 0;

	void setActive(bool);
	void setInteractable(bool);
	bool setWorldPosition(COORD);
	bool setWorldPosition(unsigned int, unsigned int);
};

