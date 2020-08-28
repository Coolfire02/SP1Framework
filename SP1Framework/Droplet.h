#pragma once
#include "GameObject.h"
class Droplet:
	public GameObject
{
private:
	WATERTYPE type;
	int DropletWorth;
public:
	std::string getType();
	int getDropletWorth();
	Droplet();
	Droplet(enum WATERTYPE type);
	~Droplet();

	Droplet* clone() const { return new Droplet(*this); };
};
