#include "Map.h"

Map::Map() {
	createMap(213, 50);
}

void Map::createMap(int x, int y) {
	xLength = x;
	yLength = y;
	map_ptr = new CHAR_INFO * [xLength];
	for (unsigned int i = 0; i < xLength; i++) {
		map_ptr[i] = new CHAR_INFO[yLength];
	}
}

void Map::setSize(int x, int y) {
	deleteMap();
	createMap(x, y);
}

Map::~Map() {
	deleteMap();
}

void Map::deleteMap() {
	for (unsigned int i = 0; i < xLength; i++) {
		delete[] map_ptr[i];
	}
	delete[] map_ptr;
}