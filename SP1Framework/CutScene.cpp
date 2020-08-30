#include "CutScene.h"


CutScene::CutScene(Console& console) : associatedConsole(console)
{
	Completed = false;
	CS_started = false;
	CS_start_time = 0;
	ms = 0;
}

CutScene::~CutScene()
{
	for (auto& element : CS_obj_ptr) { //deletes all pointers created under the cutscenes
		delete element;
	}
}

void CutScene::start()
{
	CS_started = true;
	CS_start_time = g_dElapsedTime;
	(*this).cutsceneInit();
}

void CutScene::renderMap()
{
	if (!isStarted()) return;
	Map& theMap = Scene;

	CHAR_INFO** map = theMap.getMap();
	COORD mapOffset = theMap.getMapToBufferOffset();
	for (int i = 0; i < g_consoleSize.X; i++) {
		for (int j = 0; j < g_consoleSize.Y; j++) {
			unsigned int worldX = i + mapOffset.X;
			unsigned int worldY = j + mapOffset.Y;
			bool inRangetemp = theMap.isInRange(worldX, worldY);
			if (theMap.isInRange(worldX, worldY) == true)
				associatedConsole.writeToBuffer(i, j, map[worldX][worldY].Char.AsciiChar, map[worldX][worldY].Attributes);
			else
				associatedConsole.writeToBuffer(i, j, ' ', 0x00);
		}
	}
}

void CutScene::renderObjsToMap()
{
	if (!isStarted()) return;

	Scene.clearMap();
	std::multimap<short, GameObject*> sort;

	for (auto& object_ptr : CS_obj_ptr) {
		if (!object_ptr->isActive()) continue;
		sort.insert(std::pair<short, GameObject*>(object_ptr->getWeight(), object_ptr));
	}

	for (auto& element : sort) {
		for (unsigned int x = 0; x < element.second->getXLength(); x++) {
			for (unsigned int y = 0; y < element.second->getYLength(); y++) {
				COORD mapLoc = { (short)(x + element.second->getWorldPosition().X) , (short)(y + element.second->getWorldPosition().Y) };
				if (element.second->hasRelativePos()) {
					mapLoc = { (short)(x + element.second->getRelativePos().X + Scene.getMapToBufferOffset().X) , (short)(y + element.second->getRelativePos().Y + Scene.getMapToBufferOffset().Y) };
				}
				//if this object art at this location is of a g_background, do not overwrite
				if (element.second->getArtAtLoc(x, y).Attributes == g_background.Attributes &&
					element.second->getArtAtLoc(x, y).Char.AsciiChar == g_background.Char.AsciiChar) {
					continue;
				}
				Scene.setCharAtLoc(mapLoc.X, mapLoc.Y, element.second->getArtAtLoc(x, y));
			}
		}
	}
}

COORD CutScene::getMapSize()
{
	COORD size = { (short)(Scene.getXLength()), (short)(Scene.getYLength()) };
	return size;
}

bool CutScene::isCompleted()
{
	return Completed;
}

bool CutScene::isStarted()
{
	return CS_started;
}

double CutScene::getStartTime()
{
	return CS_start_time;
}
