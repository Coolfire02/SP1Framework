#pragma once
#include "GameObject.h"

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

