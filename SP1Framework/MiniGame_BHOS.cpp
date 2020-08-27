#include "MiniGame_BHOS.h"

void MiniGame_BHOS::setMoneyText()
{
	std::string money = std::to_string(MoneyEarned);
	money = "$" + money;
	Money_ptr->setText(money);
}

std::string MiniGame_BHOS::getType()
{
	return "MiniGame_BHOS";
}

LEVELSTATE MiniGame_BHOS::getAssociatedLSState()
{
	return LS_MINIGAME_BHOS;
}

MiniGame_BHOS::MiniGame_BHOS(LEVEL level, Console& console) : MiniGame(level, console), msPassed(0)
{
	numHive = 3;
	maxPlayerLives = 3;
	playerLives = maxPlayerLives;
	selectedHive = nullptr;
	ms = 1000;
	art.setArt(MINIGAME_BHOS_ART);
	beeHiveLeft = 0;
	beeHiveRight = 0;
	grabbedHivePos = nullptr;
	MiniGameMap.setBackground(0x20);


	//Instructions for BeeHive Removal

	Text* Title = new Text("Bee Hive Removal Game", MiniGameMap.getBackground());
	Title->setRelativePos(g_consoleSize.X / 2 - Title->getText().length() / 2, 5);
	instructions_obj_ptr.push_back(Title);
	Text* Line1 = new Text("Remove bee hives by using your mouse!", MiniGameMap.getBackground());
	Line1->setRelativePos(g_consoleSize.X / 2 - Line1->getText().length() / 2, 8);
	instructions_obj_ptr.push_back(Line1);
	Text* Line2 = new Text("Click and hold onto a bee hive and gently move left and right.", MiniGameMap.getBackground());
	Line2->setRelativePos(g_consoleSize.X / 2 - Line2->getText().length() / 2, 9);
	instructions_obj_ptr.push_back(Line2);
	Text* Line3 = new Text("Be careful not to move too fast or the bees will sting!", MiniGameMap.getBackground());
	Line3->setRelativePos(g_consoleSize.X / 2 - Line3->getText().length() / 2, 10);
	instructions_obj_ptr.push_back(Line3);

	button_ptr = new Text("Start Game", 0x70);
	button_ptr->setWorldPosition(g_consoleSize.X / 2 - button_ptr->getText().length() / 2, 15);
	instructions_obj_ptr.push_back(button_ptr);
}

MiniGame_BHOS::~MiniGame_BHOS()
{
	//Intentionally left blank (deletion of obj_ptrs is handled in Level)
}

void MiniGame_BHOS::mgGameInit()
{
	srand(time(NULL)); //initial seed (does not return a value)
	//MiniGameMap.setSize(213, 50);

	Money_ptr = new Text;
	mg_obj_ptr.push_back(Money_ptr);
	Money_ptr->setRelativePos(0, 1);

	TreeMax.X = 175;
	TreeMax.Y = 41;
	TreeMin.X = 25;
	TreeMin.Y = 4;

	Text* health = new Text("Health: ", 0X7C);
	health->setRelativePos(g_consoleSize.X / 2 - health->getXLength() - 10 / 2, 2);

	health_bar = new ProgressBar(B_HORIZONTAL, 20, 3, 0xF0, 0xC0);
	health_bar->setProgress(100);
	health_bar->setRelativePos(g_consoleSize.X/2 - health_bar->getXLength()/2 + 6, 1);

	hive_selected_text = new Text("You are not holding any BeeHive currently!", 0xC0);
	hive_selected_text->setRelativePos(g_consoleSize.X / 2 - hive_selected_text->getText().length()/2, 0);

	mg_obj_ptr.push_back(health);
	mg_obj_ptr.push_back(health_bar);
	mg_obj_ptr.push_back(hive_selected_text);

	for (int b = 0; b < numHive; b++)
	{
		BeeHive* hive = new BeeHive;
		//add
		int Hives_checked;
		mg_obj_ptr.push_back(hive);
		mg_hive_ptr.push_back(hive);
		bool spotFound = false;
		while (spotFound != true) {
			int x = (rand() % TreeMax.X) + TreeMin.X;
			int y = (rand() % TreeMax.Y) + TreeMin.Y;
			hive->setWorldPosition(x, y);
			bool allNotInteracted = true;
			if (!mg_obj_ptr.empty())
			{
				for (auto& element : mg_obj_ptr)
				{
					if (hive != element && (hive->isCollided(*element)) == true)
					{
						allNotInteracted = false;
					}
				}
			}
			if (allNotInteracted == true) {
				spotFound = true;
				break;
			}
		}
	}



}

void MiniGame_BHOS::gameLoopListener()
{
	setMoneyText();
	ms += g_loopInterval;
	for (auto& falling : mg_fallingHive_ptr) {
		falling->setWorldPosition(falling->getWorldPosition().X, falling->getWorldPosition().Y + 1);
		if (falling->getWorldPosition().Y > MiniGameMap.getMapToBufferOffset().Y + g_consoleSize.Y) {
			MoneyEarned += getAssociatedLevel() * 5;
			mg_obj_ptr.erase(std::remove(mg_obj_ptr.begin(), mg_obj_ptr.end(), falling), mg_obj_ptr.end());
			delete falling;
			falling = nullptr;
		}
			
		
	}
	mg_fallingHive_ptr.erase(std::remove(mg_fallingHive_ptr.begin(), mg_fallingHive_ptr.end(), nullptr), mg_fallingHive_ptr.end());
	if (mg_hive_ptr.empty() && mg_fallingHive_ptr.empty()) {
		Completed = true;
	}
}

bool MiniGame_BHOS::processKBEvents_mg(SKeyEvent KeyEvents[])
{
	return false;
}

bool MiniGame_BHOS::processMouseEvents_mg(SMouseEvent &mouseEvent)
{
	hive_selected_text->setActive(true);
	COORD mousePos = { mouseEvent.mousePosition };
	//if (selectedHive != nullptr) Beep(5500, 50);
	switch (mouseEvent.eventFlags) {
	case 0:
		if (mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			// at the start of a left-click, this will be ran. (Only ran once)
			if (FROM_LEFT_1ST_BUTTON_PRESSED != 0) {
				if (!isInInstructions)
				{
					if (selectedHive == nullptr) {
						if (!mg_hive_ptr.empty()) {
							for (auto& element : mg_hive_ptr) {
								if (element->isInLocation(mousePos.X, mousePos.Y)) {
									selectedHive = element;
									grabbedHivePos = new COORD(mousePos);
									break;
								}
							}
						}
					}
				}
			}
		}
	case DOUBLE_CLICK: break;
	case MOUSE_WHEELED: break;
	default: break;
	}

	// if left-mouse is currently being pressed
	if (mouseEvent.buttonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
		if (selectedHive == nullptr) {
			if (!mg_hive_ptr.empty()) {
				for (auto& element : mg_hive_ptr) {
					if (element->isInLocation(mousePos.X,mousePos.Y)) {
						selectedHive = element;
						grabbedHivePos = new COORD( mousePos );
						break;
					}
				}
			}
		}
		if (selectedHive != nullptr) {
			hive_selected_text->setActive(false);
			if (mousePos.X - lastMousePos.X > 7 || mousePos.X - lastMousePos.X < - 7) {
				playerLives--;
				health_bar->setProgress(playerLives / (double)maxPlayerLives * 100);
				lastMousePos = mousePos;
				if (playerLives <= 0) Completed = true;
				
				mg_hive_ptr.erase(std::remove(mg_hive_ptr.begin(), mg_hive_ptr.end(), selectedHive), mg_hive_ptr.end());
				mg_obj_ptr.erase(std::remove(mg_obj_ptr.begin(), mg_obj_ptr.end(), selectedHive), mg_obj_ptr.end());
				delete selectedHive;
				selectedHive = nullptr;
				delete grabbedHivePos;
				grabbedHivePos = nullptr;
				beeHiveLeft = 0;
				beeHiveRight = 0;
				//TODO delete from mg_obj and hive ptr
			}
			else {
				if (grabbedHivePos != nullptr) {
					if (mousePos.X - grabbedHivePos->X < -2) {
						if (beeHiveLeft - beeHiveRight < 1) {
							if (beeHiveLeft - beeHiveRight < 0) {
								beeHiveLeft = beeHiveRight;
							}
							beeHiveLeft++;
						}
					}
					else if (mousePos.X - grabbedHivePos->X > 2) {
						if (beeHiveRight - beeHiveLeft < 1) {
							if (beeHiveRight - beeHiveLeft < 0) {
								beeHiveRight = beeHiveLeft;
							}
							beeHiveRight++;
						}
					}
					if (beeHiveRight >= 4 && beeHiveLeft >= 4) {
						beeHiveRight = 0;
						beeHiveLeft = 0;
						mg_hive_ptr.erase(std::remove(mg_hive_ptr.begin(), mg_hive_ptr.end(), selectedHive), mg_hive_ptr.end());
						mg_fallingHive_ptr.push_back(selectedHive);
						selectedHive = nullptr;
						delete grabbedHivePos;
						grabbedHivePos = nullptr;
					}
				}
			}
		}

	}
	// if left-mouse button is not pressed
	else {
		if (selectedHive != nullptr) {
			selectedHive = nullptr;
			delete grabbedHivePos;
			grabbedHivePos = nullptr;
		}
	}

	if (ms >= 20) {
		ms = 0;
		lastMousePos = mousePos;
	}
	return false;
}

void beeHiveFall(BeeHive* hive) {
	hive->setWorldPosition(hive->getWorldPosition().X, hive->getWorldPosition().Y - 1);
}
