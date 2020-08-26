#include "MiniGame_CFT.h"

MiniGame_CFT::MiniGame_CFT(LEVEL level, Console& console) : MiniGame(level, console)
{
	art.setArt(MINIGAME_CFT_ART);
}

MiniGame_CFT::~MiniGame_CFT()
{
	//Intentionally left blank
}

void MiniGame_CFT::mgGameInit()
{
	MiniGameMap.setSize(213,50);
	player_ptr = new Player;
	mg_obj_ptr.push_back(player_ptr);

	//Game Initialization
	COORD playerPos;
	playerPos.X = (MiniGameMap.getXLength() / 2 - (player_ptr->getXLength() / 2));
	playerPos.Y = (MiniGameMap.getYLength() - player_ptr->getYLength() - 1);

	player_ptr->setWorldPosition(playerPos);
}

void MiniGame_CFT::gameLoopListener()
{
	if (isStarted())
	{

	}


}

bool MiniGame_CFT::processKBEvents(SKeyEvent keyEvents[])
{
	bool eventIsProcessed = false;
	COORD player_orig_pos = player_ptr->getWorldPosition();
	COORD player_future_pos = player_orig_pos;

	if (keyEvents[K_W].keyDown) 
	{

		eventIsProcessed = true;
	}
	if (keyEvents[K_S].keyDown) 
	{

		eventIsProcessed = true;
	}
	if (keyEvents[K_A].keyDown) 
	{
		
		eventIsProcessed = true;
	}
	if (keyEvents[K_D].keyDown) 
	{
		
		eventIsProcessed = true;
	}
	if (keyEvents[K_UP].keyDown) 
	{

		eventIsProcessed = true;
	}
	if (keyEvents[K_DOWN].keyDown) 
	{

		eventIsProcessed = true;
	}
	if (keyEvents[K_LEFT].keyDown) 
	{

		eventIsProcessed = true;
	}
	if (keyEvents[K_RIGHT].keyDown) 
	{

		eventIsProcessed = true;
	}
	player_ptr->setWorldPosition(player_future_pos);

	return eventIsProcessed;
}

bool MiniGame_CFT::processMouseEvents(SMouseEvent&)
{
	return false;
}

LEVELSTATE MiniGame_CFT::getAssociatedLSState()
{
	return LS_MINIGAME_CFT;
}

std::string MiniGame_CFT::getType()
{
	return "MiniGame_CFT";
}
