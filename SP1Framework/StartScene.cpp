#include "StartScene.h"

void StartScene::cutsceneInit()
{
	fireman_ptr->setRelativePos(Scene.getXLength() / 2, 0);
	pole_ptr->setRelativePos(Scene.getXLength() / 2, Scene.getYLength() / 2);
}

StartScene::StartScene(Console& console) : CutScene(console)
{
	fireman_ptr = new ArtObject(FIREFIGHTER_ART, 800, "FireMan");
	pole_ptr = new ArtObject(POLE_ART, 300, "Pole");

	CS_obj_ptr.push_back(fireman_ptr);
	CS_obj_ptr.push_back(pole_ptr);

	Scene.setSize(213, 50);
}

StartScene::~StartScene()
{
	
}

std::string StartScene::getType()
{
	return "Start_Game_Scene";
}

void StartScene::CutSceneLoopListener()
{
	if (isStarted())
	{
		ms = 0;
		fall_delay = 0;

		if (fall_delay == 20)
		{
			fireman_ptr->setRelativePos(fireman_ptr->getWorldPosition().X, fireman_ptr->getWorldPosition().Y - 2);
			fall_delay = 0;
		}
		else
		{
			fall_delay++;
		}

		ms++;

		if (ms >= 300)
		{
			Completed = true;
		}

	}
}
