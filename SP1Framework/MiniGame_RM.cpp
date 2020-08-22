#include "MiniGame_RM.h"


std::string MiniGame_RM::getType()
{
	return "Raining Money";
}


LEVELSTATE MiniGame_RM::getAssociatedLSState()
{
	return LS_MINIGAME_RM;
}


MiniGame_RM::MiniGame_RM(LEVEL level, Console& console) : MiniGame(level, console)
{
	jar_ptr = new Jar;
	player_ptr = new Player;
	mg_obj_ptr.push_back(player_ptr);
	mg_obj_ptr.push_back(jar_ptr);
	MiniGameMap.setSize(213, 50);

	//Game initialization
	COORD playerPos;
	playerPos.X = (MiniGameMap.getXLength()/ 2 - (player_ptr->getXLength() / 2));
	playerPos.Y = (MiniGameMap.getYLength() - player_ptr->getYLength() - 1);

	player_ptr->setWorldPosition(playerPos);
	jar_ptr->setWorldPosition(playerPos.X, playerPos.Y - jar_ptr->getYLength());

	int interval = 100;
	int ms = 1000;
	srand(time(NULL));
	while (Completed != true) {
		//adding new coins to top of the map every 1000 millisecond
		if (ms >= 1000) {
			for (int i = 0; i < (rand() % 10 + 4); i++) {
				COORD coinCord = { 0,0 };
				ms = 0;
				//10 attempts
				bool colision = false;
				for (int j = 0; j < 10; j++) {
					coinCord.X = rand() % 153 + 60;
					for (auto& coin : coin_ptrs) {
						if (coin->getWorldPosition().X == coinCord.X &&
							coin->getWorldPosition().Y == coinCord.Y)
							colision = true;
					}
					if (colision == false) {
						addCoin(coinCord);
						break;
					}
				}
			}
		}

		//Making coins fall
		for (auto it = coin_ptrs.begin(); it != coin_ptrs.end(); /*NOTHING*/) {
			Coin* coin = (*it);
			COORD coord = coin->getWorldPosition();
			coord.Y -= 1;
			coin->setWorldPosition(coord);
			if (coord.Y > MiniGameMap.getMapToBufferOffset().Y + g_consoleSize.Y) {
				it = coin_ptrs.erase(it);
				delete coin;
			}
			else if (jar_ptr->isCollided(*coin)) {
				MoneyEarned += coin->getCoinWorth();
				it = coin_ptrs.erase(it);
				delete coin;
			}
		}

		ms += interval;
		Sleep(interval);
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
	if (keyEvents[K_S].keyDown) {
		future_pos.X += 2;
		eventIsProcessed = true;
	}

	return eventIsProcessed;
}

bool MiniGame_RM::processMouseEvents(SMouseEvent&)
{
	return false;
}
