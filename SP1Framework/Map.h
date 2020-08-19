#pragma once
#include <Windows.h>

class Map
{
private:
	CHAR_INFO** map_ptr;
	unsigned int xLength;
	unsigned int yLength;
	void createMap(int, int);
public:
	void deleteMap(void);
	void setSize(int, int);
	Map();
	~Map();
};

