#pragma once
#include "GameObject.h"
class Droplet:
	public GameObject
{
private:
	int DropletWorth;
public:
	std::string getType();
	int getDropletWorth();
	Droplet();
	~Droplet();

	Droplet* clone() const { return new Droplet(*this); };
};
