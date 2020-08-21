#include "Map.h"

Map::Map(int x, int y) {
	mapToBufferOffset = { 0,0 };
	createMap(x, y);
}

Map::Map() {
	mapToBufferOffset = { 0,0 };
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

void Map::clearMap() {
	for (unsigned int i = 0; i < xLength; i++) {
		for (unsigned int j = 0; j < yLength; j++) {
			if (map_ptr[i][j].Char.AsciiChar != g_background.Char.AsciiChar && map_ptr[i][j].Attributes != g_background.Attributes) {
				map_ptr[i][j] = g_background;
			}
		}
	}
}

COORD Map::getMapToBufferOffset() {
	return mapToBufferOffset;
}

bool Map::setCharAtLoc(int x, int y, CHAR_INFO character) {
	if (x < (*this).getXLength() && y < (*this).getYLength()) {
		(*this).map_ptr[x][y] = character;
	}
	return false;
}

bool Map::setMapToBufferOffset(COORD cord) {
	if ((*this).getXLength() >= (unsigned int) cord.X && (*this).getYLength() >= (unsigned int) cord.Y) {
		mapToBufferOffset = cord;
		return true;
	}
	return false;
}

bool Map::isInRange(int x, int y) {
	if (x < (*this).getXLength() && y < (*this).getYLength()) {
		return true;
	}
	return false;
}

bool Map::isInRange(COORD a) {
	if (a.X < (*this).getXLength() && a.Y < (*this).getYLength()) {
		return true;
	}
	return false;
}

unsigned int Map::getXLength() {
	return xLength;
}

unsigned int Map::getYLength() {
	return yLength;
}

CHAR_INFO** Map::getMap() {
	return map_ptr;
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