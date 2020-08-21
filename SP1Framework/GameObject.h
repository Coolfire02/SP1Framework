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
public:
	GameObject();
	~GameObject();

	bool isCollided(GameObject&);
	bool isInteractable();

	CHAR_INFO getArtAtLoc(COORD);
	CHAR_INFO getArtAtLoc(int,int);
	COORD getWorldPosition();
	unsigned int getXLength();
	unsigned int getYLength();
	bool isActive();

	virtual std::string getType() = 0;

	void setActive(bool);
	void setInteractable(bool);
	bool setWorldPosition(COORD);
	bool setWorldPosition(unsigned int, unsigned int);
};

