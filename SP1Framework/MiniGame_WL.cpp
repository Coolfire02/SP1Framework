#include "MiniGame_WL.h"

MiniGame_WL::MiniGame_WL(LEVEL level, Console& console) : MiniGame(level, console)
{
	ms = 1000;
	water_spawn_delay = 200;
	art.setArt(MINIGAME_WL_ART);
}

MiniGame_WL::~MiniGame_WL() {
}

void MiniGame_WL::gameLoopListener() {

}

bool MiniGame_WL::processKBEvents(SKeyEvent keyEvents[])
{
	COORD player_orig_pos = player_ptr->getWorldPosition();
	COORD player_future_pos = player_orig_pos;
	COORD bucket_orig_pos = bucket_ptr->getWorldPosition();
	COORD bucket_future_pos = bucket_orig_pos;
	bool eventIsProcessed = false;
	if (keyEvents[K_A].keyDown) {
		player_future_pos.X -= 2;
		bucket_future_pos.X -= 2;
		eventIsProcessed = true;
	}
	if (keyEvents[K_D].keyDown) {
		player_future_pos.X += 2;
		bucket_future_pos.X += 2;
		eventIsProcessed = true;
	}
	if (keyEvents[K_W].keyDown) {
		player_future_pos.Y -= 2;
		bucket_future_pos.Y -= 2;
		eventIsProcessed = true;
	}
	if (keyEvents[K_S].keyDown) {
		player_future_pos.Y += 2;
		bucket_future_pos.Y += 2;
		eventIsProcessed = true;
	}
	player_ptr->setWorldPosition(player_future_pos);
	bucket_ptr->setWorldPosition(bucket_future_pos);
	return eventIsProcessed;
}

bool MiniGame_WL::processMouseEvents(SMouseEvent&)
{
	return false;
}

void MiniGame_WL::setWaterText()
{
	std::string water = std::to_string(WaterCollected);
	water += water;
	Water_ptr->setText(water);
}

std::string MiniGame_WL::getType() {
	return "MiniGame_WL";
}

enum LEVELSTATE MiniGame_WL::getAssociatedLSState() {
	return LS_MINIGAME_WL;
}

void MiniGame_WL::mgGameInit() {
	bucket_ptr = new Bucket;
	player_ptr = new Player;
	Water_ptr = new Text;
	mg_obj_ptr.push_back(player_ptr);
	mg_obj_ptr.push_back(bucket_ptr);
	mg_obj_ptr.push_back(Water_ptr);
	MiniGameMap.setSize(213, 50);

	//Game initialization
	COORD playerPos;
	playerPos.X = (MiniGameMap.getXLength() / 2 - (player_ptr->getXLength() / 2));
	playerPos.Y = (MiniGameMap.getYLength() - player_ptr->getYLength() - 1);

	player_ptr->setWorldPosition(playerPos);
	bucket_ptr->setWorldPosition(playerPos.X - 1, playerPos.Y - bucket_ptr->getYLength());
	Water_ptr->setWorldPosition(0, 1);
	srand(time(NULL));
}