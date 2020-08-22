#include "Road.h"

Road::Road() 
{
	type = R_HORIZONTAL;
	art.setArt(HORIZONTAL_ROAD_ART);
	weight = 0;
}

Road::Road(ROADTYPE type) : type(type)
{
	weight = 0;
	switch (type)
	{
	case R_HORIZONTAL:
		art.setArt(HORIZONTAL_ROAD_ART);
		break;

	case R_VERTICAL:
		art.setArt(VERTICAL_ROAD_ART);
		break;
	default:
		art.setArt(HORIZONTAL_ROAD_ART);
		break;
	}
}

Road::~Road() {

}

std::string Road::getType() {
	switch (type) {
	case R_HORIZONTAL:
		return "Horizontal_Road"; break;
	case R_VERTICAL:
		return "Vertical_Road"; break;
	}
	return "Horizontal_Road";
}