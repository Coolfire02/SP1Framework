#include "StartScene.h"

void StartScene::cutsceneInit()
{
	fireman_ptr->setWorldPosition(Scene.getXLength() / 2, 0);
	pole_ptr->setRelativePos(Scene.getXLength() / 2, 0);
	truck_ptr->setWorldPosition(Scene.getXLength() / 2 + 10, 39);
}

StartScene::StartScene(Console& console) : CutScene(console)
{
	fall_delay = 0;
	move_delay = 0;
	FM_moves = 0;
	FT_moves = 0;
	fireman_ptr = new ArtObject(FIREFIGHTER_ART, 700, "FireMan");
	pole_ptr = new ArtObject(POLE_ART, 300, "Pole");
	truck_ptr = new ArtObject(FIRE_TRUCK_ART, 800, "FireTruck");

	CS_obj_ptr.push_back(fireman_ptr);
	CS_obj_ptr.push_back(pole_ptr);
	CS_obj_ptr.push_back(truck_ptr);

	Scene.setSize(213, 50);
}

StartScene::~StartScene()
{
	//Intentionally left blank
}

std::string StartScene::getType()
{
	return "Start_Game_Scene";
}

void StartScene::CutSceneLoopListener()
{
	if (isStarted())
	{
		if (getStartTime() + 7.3 < g_dElapsedTime) {
			Completed = true;
		}
		else
		{
			if ((fireman_ptr->getWorldPosition().Y + fireman_ptr->getYLength()) < 44)
			{

				if (fall_delay >= 4)
				{
					Beep(100, 100);
					int Y = (fireman_ptr->getWorldPosition().Y) + 2;
					fireman_ptr->setWorldPosition(fireman_ptr->getWorldPosition().X, Y);
					fall_delay = 0;
				}
				else
					fall_delay++;

			}
			else
			{
				if (FM_moves < 20)
				{
					move_delay++;
					if (move_delay >= 5)
					{
						fireman_ptr->setWorldPosition(fireman_ptr->getWorldPosition().X + 1, fireman_ptr->getWorldPosition().Y);
						FM_moves++;
						move_delay = 0;
					}
				}
				else
				{
					if (FT_moves < 100)
					{
						move_delay++;
						if (move_delay >= 5)
						{
							fireman_ptr->setWorldPosition(fireman_ptr->getWorldPosition().X + 3, fireman_ptr->getWorldPosition().Y);
							truck_ptr->setWorldPosition(truck_ptr->getWorldPosition().X + 3, truck_ptr->getWorldPosition().Y);
							FT_moves += 3;
						}

					}
				}
			}

		}

	}
}
