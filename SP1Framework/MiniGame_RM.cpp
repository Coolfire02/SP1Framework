#include "MiniGame_RM.h"

int ms = 1000;

std::string MiniGame_RM::getType()
{
	return "MiniGame_RM";
}

LEVELSTATE MiniGame_RM::getAssociatedLSState()
{
	return LS_MINIGAME_RM;
}

MiniGame_RM::MiniGame_RM(LEVEL level, Console& console) : MiniGame(level, console)
{
	art.setArt(MINIGAME_RM_ART);
}

void MiniGame_RM::mgGameInit() {
	jar_ptr = new Jar;
	player_ptr = new Player;
	mg_obj_ptr.push_back(player_ptr);
	mg_obj_ptr.push_back(jar_ptr);
	MiniGameMap.setSize(213, 50);

	//Game initialization
	COORD playerPos;
	playerPos.X = (MiniGameMap.getXLength() / 2 - (player_ptr->getXLength() / 2));
	playerPos.Y = (MiniGameMap.getYLength() - player_ptr->getYLength() - 1);

	player_ptr->setWorldPosition(playerPos);
	jar_ptr->setWorldPosition(playerPos.X, playerPos.Y - jar_ptr->getYLength());

	srand(time(NULL));
}

void MiniGame_RM::gameLoopListener() {
	if (isStarted()) {
		if (getStartTime() + 15.0 < g_dElapsedTime) {
			Completed = true;
		}
		else {
			int interval = 20;
			//adding new coins to top of the map every 1000 millisecond
			if (ms >= 1000) {
				int spawnCount = (rand() % 10 + 4);
				for (int i = 0; i < spawnCount; i++) {
					COORD coinCord = { 0,0 };
					ms = 0;
					//10 attempts
					bool colision = false;
					for (int j = 0; j < 10; j++) {
						coinCord.X = rand() % 153 + 60;
						coinCord.X += j;
						for (auto& coin : coin_ptrs) {
							if (coin->getWorldPosition().X == coinCord.X &&
								coin->getWorldPosition().Y == coinCord.Y)
								colision = true;
						}
						if (colision == false) {
							Beep(1440, 50);
							addCoin(coinCord);
							j = 10;
						}
					}
				}
			}

			//Making coins fall
			if (!coin_ptrs.empty()) {
				for (auto it = coin_ptrs.begin(); it != coin_ptrs.end(); /*NOTHING*/) {
					COORD coord = (*it)->getWorldPosition();
					coord.Y += 1;
					(*it)->setWorldPosition(coord);
					if (coord.Y > MiniGameMap.getMapToBufferOffset().Y + g_consoleSize.Y) {

						for (auto mg_it = mg_obj_ptr.begin(); mg_it != mg_obj_ptr.end(); /*NOTHING*/) {
							GameObject* objPtr = (*it);
							if ((*mg_it) == objPtr) {
								mg_it = mg_obj_ptr.erase(mg_it);
							}
							else {
								++mg_it;
							}
						}


						delete (*it);
						it = coin_ptrs.erase(it);

					}
					else if (jar_ptr->isCollided(*(*it))) {
						MoneyEarned += (*it)->getCoinWorth();

						for (auto mg_it = mg_obj_ptr.begin(); mg_it != mg_obj_ptr.end(); /*NOTHING*/) {
							GameObject* objPtr = (*it);
							if ((*mg_it) == objPtr) {
								mg_it = mg_obj_ptr.erase(mg_it);
							}
							else {
								++mg_it;
							}
						}
						delete (*it);
						it = coin_ptrs.erase(it);

					}
					else {
						++it;
					}
				}
			}

			ms += interval;
		}
	}
}

void MiniGame_RM::addCoin(COORD coord)
{
	Coin* coin = new Coin;
	coin->setWorldPosition(coord);
	mg_obj_ptr.push_back(coin);
	coin_ptrs.push_back(coin);
}

MiniGame_RM::~MiniGame_RM()
{

}

bool MiniGame_RM::processKBEvents(SKeyEvent keyEvents[])
{
	COORD player_orig_pos = player_ptr->getWorldPosition();
	COORD future_pos = player_orig_pos;
	bool eventIsProcessed = false;
	if (keyEvents[K_A].keyDown) {
		future_pos.X -= 2;
		eventIsProcessed = true;
	}
	if (keyEvents[K_D].keyDown) {
		future_pos.X += 2;
		eventIsProcessed = true;
	}
	player_ptr->setWorldPosition(future_pos);
	return eventIsProcessed;
}

bool MiniGame_RM::processMouseEvents(SMouseEvent&)
{
	return false;
}
