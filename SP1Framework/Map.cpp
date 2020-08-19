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
	CHAR_INFO a;
	WORD c = 0x80;
	a.Attributes = c;
	a.Char.AsciiChar = ' ';

	for (unsigned int i = 0; i < xLength; i++) {
		for (unsigned int j = 0; j < yLength; j++) {
			map_ptr[i][j] = a;
		}
	}
}

void Map::setSize(int x, int y) {
	deleteMap();
	createMap(x, y);
}

unsigned int Map::getXLength() {
	return xLength;
}

unsigned int Map::getYLength() {
	return yLength;
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