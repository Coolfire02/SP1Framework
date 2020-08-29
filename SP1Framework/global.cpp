#include "global.h"

CHAR_INFO g_background = { ' ', 0x80 };
CHAR_INFO g_errorchar = { 'E' , 0x4F };
COORD     g_consoleSize = { 213, 50 };
double    g_dElapsedTime = 0.0;
double    g_dDeltaTime = 0.0;
int       g_loopInterval = 20;

std::string round_2dp(double num)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << num;
	std::string s = stream.str();
	return s;
}