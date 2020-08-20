#include "MiniGame_WL.h"

MiniGame_WL::MiniGame_WL() {
	mapSize = { 300,300 };
}

MiniGame_WL::~MiniGame_WL() {
}

std::string MiniGame_WL::getType() {
	return "MiniGame_WL";
}

enum LEVELSTATE MiniGame_WL::getAssociatedLSState() {
	return LS_MINIGAME_WL;
}