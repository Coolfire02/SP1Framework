#include "Droplet.h"

std::string Droplet::getType()
{
	if (type == DROPLET)
		return "Droplet";
	else if (type == BOTTLE)
		return "Bottle";
	else
		return "Hail";
}

int Droplet::getDropletWorth() {
	return DropletWorth;
}

Droplet::Droplet() {
	type = DROPLET;
	art.setArt(DROPLET_ART);
	weight = 700;
	DropletWorth = 1;
}

Droplet::Droplet(enum WATERTYPE type)
{
	(*this).type = type;
	weight = 700;
	if (type == DROPLET)
	{
		art.setArt(DROPLET_ART);
		DropletWorth = 1;
	}
	else if (type == BOTTLE)
	{
		art.setArt(BOTTLE_ART);
		DropletWorth = 6;
	}
	else
	{
		art.setArt(HAIL_ART);
		DropletWorth = -2;
	}
}

Droplet::~Droplet() {

}