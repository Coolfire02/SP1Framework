#include "Stage.h"

Stage::Stage(LEVEL level) : stage(level)
{
	weight = 1000;
	art.setArt(50, 20, 0x80, 0x0F);
}

Stage::~Stage()
{
}

std::string Stage::getType() {
	return "Stage";
}

LEVEL Stage::getStage() {
	return stage;
}