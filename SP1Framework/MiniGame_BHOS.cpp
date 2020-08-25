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

MiniGame_BHOS::MiniGame_BHOS(LEVEL level, Console& console) : MiniGame(level, console)
{
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
	for (int b = 0; b < numHive; b++)
	{
		GameObject* hive = new BeeHive;
		//add
		int Hives_checked;
		mg_obj_ptr.push_back(hive);
		do
		{
			Hives_checked = 0;
			int x = (rand() % TreeMax.X) + TreeMin.X;
			int y = (rand() % TreeMax.Y) + TreeMin.Y;
			hive->setWorldPosition(x, y);
			if (!mg_obj_ptr.empty())
			{
				for (auto& element : mg_obj_ptr)
				{
					if ((hive->isCollided(*element)) == false)
					{
						Hives_checked++;
					}
				}
			}
		} while (Hives_checked != numHive);

	}



}

void MiniGame_BHOS::gameLoopListener()
{

}

bool MiniGame_BHOS::processKBEvents(SKeyEvent KeyEvents[])
{
	return false;
}

bool MiniGame_BHOS::processMouseEvents(SMouseEvent &mouseEvent)
{
	bool eventIsProcessed = true;
	COORD mousePos{ mouseEvent.mousePosition };
	
	return eventIsProcessed;
}
