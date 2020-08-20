#include "Road.h"

Road::Road() 
{
	art.setArt(HORIZONTAL_ROAD_ART);
}

Road::Road(ROADTYPE type)
{
	switch (type)
	{
	case HORIZONTAL:
		art.setArt(HORIZONTAL_ROAD_ART);
		break;

	case VERTICAL:
		art.setArt(HORIZONTAL_ROAD_ART);
		break;
	}
}

Road::~Road() {

}

std::string Road::getType() {
	return "Road";
}