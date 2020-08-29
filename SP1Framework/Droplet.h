#pragma once
#include "GameObject.h"
class Droplet:
	public GameObject
{
private:
	WATERTYPE type;
	double DropletWorth;
public:
	std::string getType();
	double getDropletWorth();
	Droplet();
	Droplet(enum WATERTYPE type);
	~Droplet();

	Droplet* clone() const { return new Droplet(*this); };
};
