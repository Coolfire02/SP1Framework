#include "MiniGame_RM.h"


void MiniGame_RM::setMoneyText()
{
	std::string money = std::to_string(MoneyEarned);
	money = "$" + money;
	Money_ptr->setText(money);
}

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
	ms = 1000;
	coin_spawn_delay = 200;
	art.setArt(MINIGAME_RM_ART);

	//To get the amounts of each coin (Coin Worth increases with each level)
	Coin NCoin(C_COIN);
	Coin BCoin(C_BIGCOIN);
	Coin RCoin(C_REDCOIN);

	coin = NCoin.getCoinWorth() + 2 * getAssociatedLevel();
	bigcoin = BCoin.getCoinWorth() + 1 * getAssociatedLevel();
	redcoin = RCoin.getCoinWorth() - 3 * getAssociatedLevel();

	//Instructions for Raining Money Game
	Text* Title = new Text("Raining Money Game", MiniGameMap.getBackground());
	Title->setRelativePos(g_consoleSize.X / 2 - Title->getText().length() / 2, 5);
	instructions_obj_ptr.push_back(Title);
	Text* Line1 = new Text("Catch coins by moving left and right using the A & D keys." , MiniGameMap.getBackground());
	Line1->setRelativePos(g_consoleSize.X / 2 - Line1->getText().length() / 2, 8);
	instructions_obj_ptr.push_back(Line1);
	Text* Line2 = new Text("Normal coins: $" + std::to_string(coin), MiniGameMap.getBackground());
	Line2->setRelativePos(g_consoleSize.X / 2 - Line2->getText().length() / 2, 9);
	instructions_obj_ptr.push_back(Line2);
	Text* Line3 = new Text("Big coins: $" + std::to_string(bigcoin), MiniGameMap.getBackground());
	Line3->setRelativePos(g_consoleSize.X / 2 - Line3->getText().length() / 2, 10);
	instructions_obj_ptr.push_back(Line3);
	Text* Line4 = new Text("Red coins: $" + std::to_string(redcoin), MiniGameMap.getBackground());
	Line4->setRelativePos(g_consoleSize.X / 2 - Line4->getText().length() / 2, 11);
	instructions_obj_ptr.push_back(Line4);

	button_ptr = new Text("Start Game", 0x70);
	button_ptr->setWorldPosition(g_consoleSize.X / 2 - button_ptr->getText().length() / 2, 16);
	instructions_obj_ptr.push_back(button_ptr);
}

void MiniGame_RM::mgGameInit() {
	srand(time(NULL));
	jar_ptr = new Jar;
	player_ptr = new Player;
	Money_ptr = new Text;
	mg_obj_ptr.push_back(player_ptr);
	mg_obj_ptr.push_back(jar_ptr);
	mg_obj_ptr.push_back(Money_ptr);
	MiniGameMap.setSize(213, 50);
	coin_fall_delay = 0;

	//Game initialization
	COORD playerPos;
	playerPos.X = (MiniGameMap.getXLength() / 2 - (player_ptr->getXLength() / 2));
	playerPos.Y = (MiniGameMap.getYLength() - player_ptr->getYLength() - 1);

	player_ptr->setWorldPosition(playerPos);
	jar_ptr->setWorldPosition(playerPos.X - 1, playerPos.Y - jar_ptr->getYLength());
	Money_ptr->setWorldPosition(0, 1);
}

void MiniGame_RM::gameLoopListener() {
	if (isStarted() && !isInInstructions) {

		setMoneyText();
		if (getStartTime() + 15.0 < g_dElapsedTime) {
			Completed = true;
		}
		else {
			int interval = 20;
			int fallRand = (rand() % 10) *10;
			//adding new coins to top of the map every 1000 millisecond
			if (ms >= 1000) {
				int spawnCount = (rand() % 10 + 4);
				for (int i = 0; i < spawnCount; i++) {
					COORD coinCord = { 0,0 };
					ms = 0;
					//10 attempts
					bool colision = false;
					for (int j = 0; j < 10; j++) {
						coinCord.X = rand() % 93 + 60;
						coinCord.X += j;
						for (auto& coin : coin_ptrs) {
							if (coin->getWorldPosition().X == coinCord.X &&
								coin->getWorldPosition().Y == coinCord.Y)
								colision = true;
						}
						if (colision == false) {
							addCoin(coinCord);
							j = 10;
						}
					}
				}
			}

			//Making coins fall
			if (coin_spawn_delay >= 100)
			{
				coin_spawn_delay = 0;
				coin_fall_delay++;
				if (!coin_ptrs.empty()) {
					for (auto it = coin_ptrs.begin(); it != coin_ptrs.end(); /*NOTHING*/) {
						COORD coord = (*it)->getWorldPosition();
						if (coin_fall_delay >= 2 && (((*it)->getType()) == "Big_Coin"))
						{
							coord.Y += 1;
						}
						else if ((*it)->getType() != "Big_Coin")
						{
							coord.Y += 1;
						}
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
							int CoinWorth;
							if ((*it)->getType() == "Coin")
								CoinWorth = coin;
							else if ((*it)->getType() == "Big_Coin")
								CoinWorth = bigcoin;
							else if ((*it)->getType() == "Red_Coin")
								CoinWorth = redcoin;
							else
								CoinWorth = coin;
							MoneyEarned += CoinWorth;

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
				if (coin_fall_delay >= 2)
					coin_fall_delay = 0;
			}

			ms += fallRand;
			coin_spawn_delay += interval;
		}
	}
}

void MiniGame_RM::addCoin(COORD coord)
{
	Coin* coin = NULL;
	int randomizer = (rand() % 10);
	if ((randomizer == 5)  || (randomizer == 2) || (randomizer == 7) || (randomizer == 9))
		coin = new Coin(C_REDCOIN);
	else if((randomizer == 1))
		coin = new Coin(C_BIGCOIN);
	else
		coin = new Coin(C_COIN);
	coin->setWorldPosition(coord);
	mg_obj_ptr.push_back(coin);
	coin_ptrs.push_back(coin);
}

MiniGame_RM::~MiniGame_RM()
{
	//Intentionally left blank (deletion of obj_ptrs is handled in Level)
}

bool MiniGame_RM::processKBEvents_mg(SKeyEvent keyEvents[])
{
	COORD player_orig_pos = player_ptr->getWorldPosition();
	COORD player_future_pos = player_orig_pos;
	COORD jar_orig_pos = jar_ptr->getWorldPosition();
	COORD jar_future_pos = jar_orig_pos;
	bool eventIsProcessed = false;
	if (keyEvents[K_A].keyDown) {
		player_future_pos.X -= 2;
		jar_future_pos.X -= 2;
		eventIsProcessed = true;
	}
	if (keyEvents[K_D].keyDown) {
		player_future_pos.X += 2;
		jar_future_pos.X += 2;
		eventIsProcessed = true;
	}
	player_ptr->setWorldPosition(player_future_pos);
	jar_ptr->setWorldPosition(jar_future_pos);
	return eventIsProcessed;
}

bool MiniGame_RM::processMouseEvents_mg(SMouseEvent&)
{
	return false;
}
