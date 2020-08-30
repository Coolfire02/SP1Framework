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
	CHAR_INFO background;
public:
	void deleteMap(void);
	void setSize(int, int);
	void clearMap();
	COORD getMapToBufferOffset();
	bool isInRange(unsigned int, unsigned int);
	bool isInRange(COORD);
	void setBackground(WORD bg);
	bool setMapToBufferOffset(COORD);
	bool setCharAtLoc(unsigned int, unsigned int, CHAR_INFO);
	CHAR_INFO getCharAtLoc(int, int);
	CHAR_INFO** getMap();
	unsigned int getXLength();
	unsigned int getYLength();
	WORD getBackground();
	Map(int,int);
	Map();
	~Map();
};