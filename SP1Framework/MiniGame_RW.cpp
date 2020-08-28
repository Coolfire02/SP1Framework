#include "MiniGame_RW.h"

void MiniGame_RW::setWaterText()
{
	std::string water = std::to_string(WaterCollected);
	water = water + "gallon";
	Water_ptr->setText(water);
}
std::string MiniGame_RW::getType()
{
	return "MiniGame_RW";
}

LEVELSTATE MiniGame_RW::getAssociatedLSState()
{
	return LS_MINIGAME_RW;
}
MiniGame_RW::MiniGame_RW(LEVEL level, Console& console) : MiniGame(level, console)
{
	ms = 1000;
	droplet_spawn_delay = 200;
	droplet_fall_delay = 0;
	art.setArt(MINIGAME_RW_ART);

	//To get the amounts of each water (water Worth increases with each level)
	Droplet NDroplet(DROPLET);
	Droplet Bottle(BOTTLE);
	Droplet Hail(HAIL);

	Text* Title = new Text("Raining water Game", MiniGameMap.getBackground());
	Title->setRelativePos(g_consoleSize.X / 2 - Title->getText().length() / 2, 5);
	instructions_obj_ptr.push_back(Title);
	Text* Line1 = new Text("Collect rainwater by moving left and right using the A & D keys.", MiniGameMap.getBackground());
	Line1->setRelativePos(g_consoleSize.X / 2 - Line1->getText().length() / 2, 8);
	instructions_obj_ptr.push_back(Line1);
	Text* Line2 = new Text("Normal droplets give you " + std::to_string(NDroplet.getDropletWorth()) + " litre", MiniGameMap.getBackground());
	Line2->setRelativePos(g_consoleSize.X / 2 - Line2->getText().length() / 2, 9);
	instructions_obj_ptr.push_back(Line2);
	Text* Line3 = new Text("Bottles give you " + std::to_string(Bottle.getDropletWorth()) + " litre", MiniGameMap.getBackground());
	Line3->setRelativePos(g_consoleSize.X / 2 - Line3->getText().length() / 2, 10);
	instructions_obj_ptr.push_back(Line3);
	Text* Line4 = new Text("Hails give you " + std::to_string(Hail.getDropletWorth()) + "litres", MiniGameMap.getBackground());
	Line4->setRelativePos(g_consoleSize.X / 2 - Line4->getText().length() / 2, 11);
	instructions_obj_ptr.push_back(Line4);
	

	button_ptr = new Text("Start Game", 0x70);
	button_ptr->setWorldPosition(g_consoleSize.X / 2 - button_ptr->getText().length() / 2, 15);
	instructions_obj_ptr.push_back(button_ptr);
}

void MiniGame_RW::mgGameInit() {
	jar_ptr = new Jar;
	player_ptr = new Player;
	Water_ptr = new Text;
	mg_obj_ptr.push_back(player_ptr);
	mg_obj_ptr.push_back(jar_ptr);
	mg_obj_ptr.push_back(Water_ptr);
	MiniGameMap.setSize(213, 50);

	//Game initialization
	COORD playerPos;
	playerPos.X = (MiniGameMap.getXLength() / 2 - (player_ptr->getXLength() / 2));
	playerPos.Y = (MiniGameMap.getYLength() - player_ptr->getYLength() - 1);

	player_ptr->setWorldPosition(playerPos);
	jar_ptr->setWorldPosition(playerPos.X - 1, playerPos.Y - jar_ptr->getYLength());
	Water_ptr->setWorldPosition(0, 1);
}

void MiniGame_RW::gameLoopListener() {
	if (isStarted() && !isInInstructions) {

		setWaterText();
		if (getStartTime() + 15.0 < g_dElapsedTime) {
			Completed = true;
		}
		else {
			int interval = 20;
			int fallrand = (rand() % 10)*10;
			//adding new droplet to top of the map every 1000 millisecond
			if (ms >= 100) {
				int spawnCount = (rand() % 10 + 4);
				for (int i = 0; i < spawnCount; i++) {
					COORD waterCord = { 0,0 };
					ms = 0;
					//10 attempts
					bool colision = false;
					for (int j = 0; j < 10; j++) {
						waterCord.X = rand() % 93 + 60;
						waterCord.X += j;
						for (auto& droplet : droplet_ptrs) {
							if (droplet->getWorldPosition().X == waterCord.X &&
								droplet->getWorldPosition().Y == waterCord.Y)
								colision = true;
						}
						if (colision == false) {
							addWater(waterCord);
							j = 10;
						}
					}
				}
			}

			//Making droplets fall
			if (droplet_spawn_delay >= 10)
			{
				droplet_spawn_delay = 0;
				droplet_fall_delay++;
				if (!droplet_ptrs.empty()) {
					for (auto it = droplet_ptrs.begin(); it != droplet_ptrs.end(); /*NOTHING*/) {
						COORD coord = (*it)->getWorldPosition();
						if (droplet_fall_delay >= 10 && (((*it)->getType()) == "Bottle"))
						{
							coord.Y += 1;
						}
						else if ((*it)->getType()!= "Bottle")
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
							it = droplet_ptrs.erase(it);

						}
						else if (jar_ptr->isCollided(*(*it))) {
							WaterCollected += (*it)->getDropletWorth();

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
							it = droplet_ptrs.erase(it);

						}
						else {
							++it;
						}
					}
				}
				if (droplet_fall_delay >= 10)
					droplet_fall_delay = 0;
			}

			ms += fallrand;
			droplet_spawn_delay += interval;
		}
	}
}

void MiniGame_RW::addWater(COORD coord)
{
	Droplet* droplet = NULL;
	int randomizer = (rand() % 100);
	if (randomizer < 10)
		droplet = new Droplet(HAIL);
	else if (randomizer == 40)
		droplet = new Droplet(BOTTLE);
	else
		droplet = new Droplet(DROPLET);
	droplet->setWorldPosition(coord);
	mg_obj_ptr.push_back(droplet);
	droplet_ptrs.push_back(droplet);
}

MiniGame_RW::~MiniGame_RW()
{
	//Intentionally left blank (deletion of obj_ptrs is handled in Level)
}

bool MiniGame_RW::processKBEvents_mg(SKeyEvent keyEvents[])
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

bool MiniGame_RW::processMouseEvents_mg(SMouseEvent&)
{
	return false;
}
