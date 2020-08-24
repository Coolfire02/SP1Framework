#include "Road.h"

Road::Road() 
{
	type = R_HORIZONTAL;
	art.setArt(HORIZONTAL_ROAD_ART);
	weight = 0;
}

Road::Road(ROADTYPE type) : type(type)
{
	weight = 0;
	switch (type)
	{
	case R_HORIZONTAL:
		art.setArt(HORIZONTAL_ROAD_ART);
		break;

	case R_VERTICAL:
		art.setArt(VERTICAL_ROAD_ART);
		break;
	case R_L:
		art.setArt(L_ROAD_ART);
		break;
	case R_RL:
		art.setArt(RL_ROAD_ART);
		break;
	case R_LUL:
		art.setArt(LUL_ROAD_ART);
		break;
	case R_RUL:
		art.setArt(RUL_ROAD_ART);
		break;
	case R_DT:
		art.setArt(DT_ROAD_ART);
		break;
	case R_UT:
		art.setArt(RL_ROAD_ART);
		break;
	case R_LVT:
		art.setArt(LVT_ROAD_ART);
		break;
	case R_RVT:
		art.setArt(RVT_ROAD_ART);
		break;
	case R_X:
		art.setArt(X_ROAD_ART);
		break;
	default:
		art.setArt(HORIZONTAL_ROAD_ART);
		break;
	}
}

Road::~Road() {

}

std::string Road::getType() 
{
	switch (type) 
	{
	case R_HORIZONTAL:
		return "Horizontal_Road"; 
		break;
	case R_VERTICAL:
		return "Vertical_Road"; 
		break;
	case R_L:
		return "L_Road";
		break;
	case R_RL:
		return "Right_L_Road";
		break;
	case R_LUL:
		return "Left_Up_L_Road";
		break;
	case R_RUL:
		return "Right_Up_L_Road";
		break;
	case R_DT:
		return "Down_T_Road";
		break;
	case R_UT:
		return "Up_T_Road";
		break;
	case R_LVT:
		return "Left_Vertical_T_Road";
		break;
	case R_RVT:
		return "Right_Vertical_T_Road";
		break;
	case R_X:
		return "Cross_Road";
		break;

	default:
		return "Horizontal_Road"; break;
	}

}