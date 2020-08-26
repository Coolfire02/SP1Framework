#include "Droplet.h"

std::string Droplet::getType()
{
	return "Droplet";
}

int Droplet::getDropletWorth() {
	return DropletWorth;
}

Droplet::Droplet() {
	art.setArt(DROPLET_ART);
	weight = 700;
	DropletWorth = 1;
}

Droplet::~Droplet() {

}