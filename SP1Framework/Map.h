#pragma once
#include "global.h"
#include <Windows.h>

class Map
{
private:
	CHAR_INFO** map_ptr;
	unsigned int xLength;
	unsigned int yLength;
	void createMap(int, int);
	COORD mapToBufferOffset;
public:
	void deleteMap(void);
	void setSize(int, int);
	void clearMap();
	COORD getMapToBufferOffset();
	bool isInRange(int,int);
	bool isInRange(COORD);
	bool setMapToBufferOffset(COORD);
	bool setCharAtLoc(int, int, CHAR_INFO);
	CHAR_INFO** getMap();
	unsigned int getXLength();
	unsigned int getYLength();
	Map(int,int);
	Map();
	~Map();
};
