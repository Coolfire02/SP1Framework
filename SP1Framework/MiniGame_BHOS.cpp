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
	maxPlayerLives = 5;
	playerLives = maxPlayerLives;
	selectedHive = nullptr;
	ms = 1000;
	numHive = 3;
	art.setArt(MINIGAME_BHOS_ART);
}

MiniGame_BHOS::~MiniGame_BHOS()
{
	//Intentionally left blank (deletion of obj_ptrs is handled in Level)
}

void MiniGame_BHOS::mgGameInit()
{
	srand(time(NULL)); //initial seed (does not return a value)
	MiniGameMap.setSize(213, 50);

	TreeMax.X = 175;
	TreeMax.Y = 41;
	TreeMin.X = 25;
	TreeMin.Y = 4;

	health_bar = new ProgressBar(B_HORIZONTAL, 20, 3, 0xF0, 0xC0);
	health_bar->setProgress(100);
	mg_obj_ptr.push_back(health_bar);

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
			Beep(5500, 50);
		}
	}



}

void MiniGame_BHOS::gameLoopListener()
{
	ms += g_loopInterval;
}

bool MiniGame_BHOS::processKBEvents(SKeyEvent KeyEvents[])
{
	return false;
}

bool MiniGame_BHOS::processMouseEvents(SMouseEvent &mouseEvent)
{
	COORD mousePos = { mouseEvent.mousePosition };
	if (selectedHive != nullptr) Beep(5500, 50);
	switch (mouseEvent.eventFlags) {
	case 0:
		if (mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			// at the start of a left-click, this will be ran. (Only ran once)
			if (FROM_LEFT_1ST_BUTTON_PRESSED != 0) {
				if (selectedHive == nullptr) {
					if (!mg_hive_ptr.empty()) {
						for (auto& element : mg_hive_ptr) {
							if (element->isInLocation(MiniGameMap.getMapToBufferOffset().X + mousePos.X, MiniGameMap.getMapToBufferOffset().Y + mousePos.Y)) {
								selectedHive = element;
								return true;
								break;
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
		if (selectedHive != nullptr) {
			if (mousePos.X - lastMousePos.X > 4 || mousePos.X - lastMousePos.X < -4) {
				Beep(5000, 50);
				playerLives--;
				health_bar->setProgress(playerLives / (double)maxPlayerLives * 100);
				lastMousePos = mousePos;
				if (playerLives <= 0) Completed = true;
				selectedHive = nullptr;
				//TODO delete from mg_obj and hive ptr
			}
			else {
				//Beep(8000, 50);
			}
		}

	}
	// if left-mouse button is not pressed
	else {
		if (selectedHive != nullptr)
			selectedHive = nullptr;
	}

	if (ms >= 20) {
		ms = 0;
		lastMousePos = mousePos;
	}
	return false;
}
