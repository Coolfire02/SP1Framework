#include "MiniGame_WL.h"

MiniGame_WL::MiniGame_WL(LEVEL level, Console& console) : MiniGame(level, console)
{
	
}

MiniGame_WL::~MiniGame_WL() {
}

void MiniGame_WL::gameLoopListener() {

}

bool MiniGame_WL::processKBEvents(SKeyEvent[])
{
	return false;
}

bool MiniGame_WL::processMouseEvents(SMouseEvent&)
{
	return false;
}

std::string MiniGame_WL::getType() {
	return "MiniGame_WL";
}

enum LEVELSTATE MiniGame_WL::getAssociatedLSState() {
	return LS_MINIGAME_WL;
}