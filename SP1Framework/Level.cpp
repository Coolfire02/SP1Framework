#include "Level.h"

Level::Level(LEVEL level)
{
	(*this).level = level;
	map.setSize(1000, 300);

}

Level::~Level()
{
}
