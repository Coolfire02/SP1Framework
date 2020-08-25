#include "Forest.h"

Forest::Forest() {
	art.setArt(FOREST_ART);
}

Forest::~Forest() {
	// intentionally left blank
}

std::string Forest::getType() {
	return "Forest";
}