#include "Road.h"

Road::Road() 
{
	setRoadType(R_HORIZONTAL);
	weight = 0;
}

Road::Road(ROADTYPE type)
{
	weight = 0;
	setRoadType(type);
}

void Road::setRoadType(ROADTYPE type) {
	(*this).type = type;
	switch (type)
	{
	case R_HORIZONTAL:
		art.setArt(HORIZONTAL_ROAD_ART);
		break;
	case R_VERTICAL:
		art.setArt(VERTICAL_ROAD_ART);
		break;
	case R_HORIZONTAL_SHORT:
		art.setArt(HORIZONTAL_ROAD_SHORT_ART);
		break;
	case R_VERTICAL_SHORT:
		art.setArt(VERTICAL_ROAD_SHORT_ART);
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

void Road::rotateRoadType() {
	type = static_cast<ROADTYPE>(type+1);
	if (type == R_COUNT) {
		type = R_HORIZONTAL;
	}
	(*this).setRoadType(type);
}

Road::~Road() {

}

ROADTYPE Road::getRoadType() {
	return type;
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
	case R_HORIZONTAL_SHORT:
		return "Horizontal_Short_Road";
		break;
	case R_VERTICAL_SHORT:
		return "Vertical_Short_Road";
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