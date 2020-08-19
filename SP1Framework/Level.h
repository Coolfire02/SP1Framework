#pragma once
#include "GameObject.h"
#include"FireTruck.h"
#include"GameObject.h"
#include"ASCII.h"


class Level
{
private:
	GameObject* objs; 
public:
	Level();
	~Level();
};

enum LEVELS {
	MAIN,
	TUTORIAL,
	STAGE_1_LEVEL_1,
	STAGE_2_LEVEL_1,
	STAGE_BUILDER,
	GRAPHICS_BUILDER
};




