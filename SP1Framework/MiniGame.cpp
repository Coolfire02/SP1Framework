#include "MiniGame.h"

MiniGame::MiniGame(LEVEL level, Console& console) : associatedConsole(console), associatedLevel(level)
{
	Completed = false;
	WaterCollected = 0;
	MoneyEarned = 0;

	mapSize = g_consoleSize;
	weight = 1000;
}


bool MiniGame::CompletionCheck()
{
	return Completed;
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

void MiniGame::renderObjsToMap(int gameType)
{
	switch (gameType)
	{
	case(MINIGAME_BHOS):

		break;
	
	case(MINIGAME_CE):

		break;

	case(MINIGAME_CFT):

		break;

	case(MINIGAME_PCE):

		break;

	case(MINIGAME_RM):

		break;

	case(MINIGAME_RW):

		break;

	case(MINIGAME_WFAR):

		break;

	case(MINIGAME_WL):

		break;

	case(MINIGAME_WREST):

		break;

	}
}

bool MiniGame::processKBEvents(SKeyEvent[])
{
	return false;
}

bool MiniGame::processMouseEvents(SMouseEvent&)
{
	return false;
}

int MiniGame::getWaterCollected()
{
	return WaterCollected;
}

int MiniGame::getMoneyEarned()
{
	return MoneyEarned;
}

void MiniGame::UpdateMinigamewithKeyFunctions()
{

}

COORD MiniGame::getMapSize()
{
	return mapSize;
}

MiniGame::~MiniGame()
{
	
}
