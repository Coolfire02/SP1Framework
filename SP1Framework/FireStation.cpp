#include "FireStation.h"

FireStation::FireStation() {
	art.setArt(FIRE_STATION_ART);
}

FireStation::~FireStation() {
	// intentionally left blank
}

std::string FireStation::getType() {
	return "FireStation";
}