#include "MiniGame.h"

MiniGame::MiniGame(LEVEL level, Console& console) : associatedConsole(console), associatedLevel(level)
{
	mg_started = false;
	mg_start_time = g_dElapsedTime;
	player_ptr = NULL;
	Completed = false;
	WaterCollected = 0;
	MoneyEarned = 0;
	weight = 1000;
}


bool MiniGame::isCompleted()
{
	return Completed;
}

void MiniGame::start() {
	mg_started = true;
	mg_start_time = g_dElapsedTime;
	(*this).mgGameInit();
}

void MiniGame::setWaterCollected(int w)
{
	WaterCollected = w;
}

void MiniGame::setMoneyEarned(int m)
{
	MoneyEarned = m;
}

void MiniGame::renderMap()
{
	if (!isStarted()) return;
	CHAR_INFO** map = MiniGameMap.getMap();
	COORD mapOffset = MiniGameMap.getMapToBufferOffset();
	for (int i = 0; i < g_consoleSize.X; i++) {
		for (int j = 0; j < g_consoleSize.Y; j++) {
			unsigned int worldX = i + mapOffset.X;
			unsigned int worldY = j + mapOffset.Y;
			bool inRangetemp = MiniGameMap.isInRange(worldX, worldY);
			if (MiniGameMap.isInRange(worldX, worldY) == true)
				associatedConsole.writeToBuffer(i, j, map[worldX][worldY].Char.AsciiChar, map[worldX][worldY].Attributes);
			else
				associatedConsole.writeToBuffer(i, j, ' ', 0x00);
		}
	}

}

void MiniGame::renderObjsToMap()
{
	if (!isStarted()) return;

	MiniGameMap.clearMap();
	std::multimap<short, GameObject*> sort;
	for (auto& object_ptr : mg_obj_ptr) {
		if (!object_ptr->isActive()) continue;
		sort.insert(std::pair<short, GameObject*>(object_ptr->getWeight(), object_ptr));
	}
	for (auto& element : sort) {
		for (int x = 0; x < element.second->getXLength(); x++) {
			for (int y = 0; y < element.second->getYLength(); y++) {
				COORD mapLoc = { x + element.second->getWorldPosition().X , y + element.second->getWorldPosition().Y };
				if (element.second->hasRelativePos()) {
					mapLoc = { (short)(x + element.second->getRelativePos().X + MiniGameMap.getMapToBufferOffset().X) , (short)(y + element.second->getRelativePos().Y + MiniGameMap.getMapToBufferOffset().Y) };
				}
				//if this object art at this location is of a g_background, do not overwrite
				if (element.second->getArtAtLoc(x, y).Attributes == g_background.Attributes &&
					element.second->getArtAtLoc(x, y).Char.AsciiChar == g_background.Char.AsciiChar) {
					continue;
				}
				MiniGameMap.setCharAtLoc(mapLoc.X, mapLoc.Y, element.second->getArtAtLoc(x, y));
			}
		}
	}
}

double MiniGame::getStartTime() {
	return mg_start_time;
}

bool MiniGame::isStarted() {
	return mg_started;
}

int MiniGame::getWaterCollected()
{
	return WaterCollected;
}

int MiniGame::getMoneyEarned()
{
	return MoneyEarned;
}

LEVEL MiniGame::getAssociatedLevel() {
	return associatedLevel;
}

COORD MiniGame::getMapSize()
{
	COORD size = { MiniGameMap.getXLength(), MiniGameMap.getYLength() };
	return size;
}

MiniGame::~MiniGame()
{
	for (auto& element : mg_obj_ptr) { //deletes all pointers created under the minigames
		delete element;
	}
}
