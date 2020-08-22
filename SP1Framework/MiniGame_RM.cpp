#include "MiniGame_RM.h"


std::string MiniGame_RM::getType()
{
	return "Raining Money";
}


LEVELSTATE MiniGame_RM::getAssociatedLSState()
{
	return LEVELSTATE();
}


MiniGame_RM::MiniGame_RM(LEVEL level, Console& console) : MiniGame(level, console)
{
	jar_ptr = new Jar;
	player_ptr = new Player;
	mg_obj_ptr.push_back(player_ptr);
	mg_obj_ptr.push_back(jar_ptr);
	mapSize = { 300, 300 };
	player_ptr->setWorldPosition(150, 280);
}

void MiniGame_RM::addCoin()
{
	coin_ptr = new Coin;
	mg_obj_ptr.push_back(coin_ptr);
}

MiniGame_RM::~MiniGame_RM()
{

}

bool MiniGame_RM::processKBEvents(SKeyEvent keyEvents[])
{
	COORD player_orig_pos = player_ptr->getWorldPosition();
	COORD future_pos = player_orig_pos;
	bool eventIsProcessed = false;
	if (keyEvents[K_W].keyDown)

	return false;
}

bool MiniGame_RM::processMouseEvents(SMouseEvent&)
{
	return false;
}
