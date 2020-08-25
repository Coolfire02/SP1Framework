#include "ASCII.h"



ASCII::ASCII() {
	xLength = 0;
	yLength = 0;
	art = nullptr;
}

ASCII::ASCII(ARTTYPE type) {
	xLength = 0;
	yLength = 0;
	art = nullptr;
	(*this).setArt(type);
}

ASCII::~ASCII() {
	for (unsigned int i = 0; i < xLength; i++) {
		delete[] art[i];
	}
	delete[] art;
}

void ASCII::tokenize(std::string const& str, const char delim,
	std::vector<std::string>& out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

bool ASCII::setArt(ARTTYPE type) {
	xLength = 0;
	yLength = 0;
	int lineNum = 0;
	const char delim = ',';
	std::string line1;
	std::string line2;
	std::string folder = "ASCII_art\\";
	std::string arttxt;
	switch (type)
	{
	case FIREFIGHTER_ART:
		arttxt = "Fireman.txt";
		break;
	case FIRE_TRUCK_ART:
		arttxt = "FireTruck.txt";
		break;
	case FIRE_STATION_ART:
		arttxt = "FireStation.txt";
		break;
	case RESERVOIR_ART:
		arttxt = "Reservoir.txt";
		break;


	case MINIGAME_RM_ART:
		arttxt = "MiniGame_RM.txt";
		break;

	case MINIGAME_WL_ART:
		arttxt = "MiniGame_WL.txt";
		break;


	case HORIZONTAL_ROAD_ART:
		arttxt = "Roads\\Hroad.txt";
		break;
	case VERTICAL_ROAD_ART:
		arttxt = "Roads\\Vroad.txt";
		break;
	case L_ROAD_ART:
		arttxt = "Roads\\Lroad.txt";
		break;
	case RL_ROAD_ART:
		arttxt = "Roads\\RLroad.txt";
		break;
	case LUL_ROAD_ART:
		arttxt = "Roads\\LULroad.txt";
		break;
	case RUL_ROAD_ART:
		arttxt = "Roads\\RULroad.txt";
		break;
	case DT_ROAD_ART:
		arttxt = "Roads\\DTroad.txt";
		break;
	case UT_ROAD_ART:
		arttxt = "Roads\\UTroad.txt";
		break;
	case LVT_ROAD_ART:
		arttxt = "Roads\\LVTroad.txt";
		break;
	case RVT_ROAD_ART:
		arttxt = "Roads\\RVTroad.txt";
		break;
	case X_ROAD_ART:
		arttxt = "Roads\\Xroad.txt";
		break;

	case CAT_ART:
		arttxt = "Cat.txt";
		break;
	case TREE_ART:
		arttxt = "Tree.txt";
		break;

	case BEEHIVE_ART:
		arttxt = "BeeHive.txt";
		break;

	case COIN_ART:
		arttxt = "Coin.txt";
		break;
	case JAR_ART:
		arttxt = "Jar.txt";
		break;
	case PIPE_ART:
		arttxt = "Pipe.txt";
		break;
	case WRENCH_HEAD_ART:
		arttxt = "Wrench_Head.txt";
		break;
	case WRENCH_TAIL_ART:
		arttxt = "Wrench_Tail.txt";
		break;
	case BUCKET_ART:
		arttxt = "Bucket.txt";
		break;
	default:
		arttxt = "NA";
		break;
	}

	arttxt = folder + arttxt;

	if (arttxt != "NA")
	{
		std::ifstream ReadFile1(arttxt);

		if (ReadFile1.is_open())
		{
			while (std::getline(ReadFile1, line1))
			{

				int pos = 0; //To check what position it is checking in each line of the txt.
				std::vector<std::string> out;
				tokenize(line1, delim, out); //To split the lines depending on where ',' is.

				if (lineNum == 0)
				{
					for (auto& line1 : out)
					{
						if (pos == 0)
						{
							xLength = std::stoi(line1);
							pos++;
						}
						else
							yLength = std::stoi(line1);
					}

				}
				break;
			}
		}
		ReadFile1.close();


		if (xLength > 0 && yLength > 0)
		{
			art = new CHAR_INFO * [xLength];
			for (unsigned int i = 0; i < xLength; i++) {
				art[i] = new CHAR_INFO[yLength];
			}

			for (unsigned int i = 0; i < xLength; i++) {
				for (unsigned int j = 0; j < yLength; j++) {
					art[i][j] = g_background;
				}
			}

			std::ifstream ReadFile2(arttxt);
			std::string line2;
			if (ReadFile2.is_open())
			{
				const char delim = ',';
				int numPixel = 0;
				int index = 0;
				while (std::getline(ReadFile2, line2))
				{	
					int x = 0, y = 0;
					//Initialization of pixel
					CHAR_INFO pixel = g_background;

					int pos = 0; //To check what position it is checking in the txt file
					std::vector<std::string> out;
					tokenize(line2, delim, out);


					for (auto& line2 : out)
					{
						if (index >= 1)
						{
							if (pos == 0)
							{
								unsigned int thecolor = std::stoul(line2, nullptr, 16);
								WORD theAttri = thecolor;
								pixel.Attributes = theAttri;
							}
							else if (pos == 1)
								pixel.Char.AsciiChar = std::stoi(line2);
							else if (pos == 2)
								x = std::stoi(line2);
							else
								y = std::stoi(line2);

						}
						pos++;

					}
					if(index > 0)
						art[x][y] = pixel;
					index++;
				}

				ReadFile2.close();
			}

			//for every line in text
			//art[x][y] = ada;
			return true;
		}
	}

	else 
	{
		art = nullptr;
	}
	return false;
}

bool ASCII::setArt(BAR barType, short width, short height, WORD border, WORD fill, double progress) {
	if (art != nullptr) {
		deleteArt();
	}
	art = new CHAR_INFO * [xLength];
	for (unsigned int i = 0; i < xLength; i++) {
		art[i] = new CHAR_INFO[yLength];
	}
	CHAR_INFO borderChar = g_background;
	borderChar.Attributes = border;
	for (unsigned int i = 0; i < xLength; i++) {
		for (unsigned int j = 0; j < yLength; j++) {
			art[i][j] = borderChar;

		}
	}
	if (progress > 100) progress = 100;
	short insideWidth, insideHeight;
	insideWidth = width - 2;
	insideHeight = height - 2;
	int totalBars = 0;
	int usedBars = 0;
	switch (barType) {
	case B_HORIZONTAL:
		totalBars = insideWidth;
		usedBars = round((progress / 100) * totalBars);
		for (int i = 1; i <= insideWidth; i++) {
			for (int j = 1; j <= insideHeight; j++) {
				if (i <= usedBars) {
					art[i][j].Attributes = fill;
				}
				else {
					WORD word = g_background.Attributes;
					art[i][j].Attributes = word;
				}
			}
		}
		break;
	case B_VERTICAL:
		totalBars = insideHeight;
		usedBars = round((progress / 100) * totalBars);
		int count = 0;
		for (int i = height-1; i >= 1; i--) {
			count++;
			for (int j = 1; j <= insideWidth; j++) {
				if (count <= usedBars) {
					art[i][j].Attributes = fill;
				}
				else {
					art[i][j].Attributes = g_background.Attributes;
				}
			}
		}
		break;
	}
	return true;
}

bool ASCII::setArt(std::string txt)
{
	CHAR_INFO txt_bg;
	txt_bg.Attributes = 0x20;
	yLength = 1;
	xLength = txt.length();

	art = new CHAR_INFO * [xLength];
	for (unsigned int i = 0; i < xLength; i++) {
		art[i] = new CHAR_INFO[yLength];
	}

	for (unsigned int i = 0; i < xLength; i++) {
		for (unsigned int j = 0; j < yLength; j++) {
			art[i][j] = txt_bg;
		}
	}

	for (unsigned int t = 0; t < txt.length(); t++)
	{
		art[t][0].Char.AsciiChar = txt[t];
	}
	return true;
}

bool ASCII::setArt(std::string txt, WORD bg)
{
	CHAR_INFO txt_bg;
	txt_bg.Attributes = bg;
	yLength = 1;
	xLength = txt.length();

	art = new CHAR_INFO * [xLength];
	for (unsigned int i = 0; i < xLength; i++) {
		art[i] = new CHAR_INFO[yLength];
	}

	for (unsigned int i = 0; i < xLength; i++) {
		for (unsigned int j = 0; j < yLength; j++) {
			art[i][j] = txt_bg;
		}
	}

	for (unsigned int t = 0; t < txt.length(); t++)
	{
		art[t][0].Char.AsciiChar = txt[t];
	}
	return true;
}

bool ASCII::setArt(int width, int height, WORD bg, WORD border)
{
	xLength = width;
	yLength = height;

	CHAR_INFO background;
	CHAR_INFO border_color;
	border_color.Attributes = border;
	background.Attributes = bg;
	yLength = width;
	xLength = height;

	art = new CHAR_INFO * [xLength];
	for (unsigned int i = 0; i < xLength; i++) 
	{
		for (unsigned int j = 0; j < yLength; j++)
		{
			art[i] = new CHAR_INFO[yLength];
		}
	}

	for (unsigned int i = 0; i < xLength; i++) 
	{
		for (unsigned int j = 0; j < yLength; j++) {
			art[i][j] = background;
		}
	}
	if ((yLength >= 3) && (xLength >= 3))
	{
		for (unsigned int i = 0; i < xLength; i++)
		{
			art[i][0] = border_color;
			art[i][yLength - 1] = border_color;
		}
		for (unsigned int j = 0; j < yLength; j++)
		{
			art[0][j] = border_color;
			art[xLength - 1][j] = border_color;
		}
	}
	return true;
}

void ASCII::deleteArt()
{
	xLength = 0;
	yLength = 0;
	for (unsigned int i = 0; i < xLength; i++) {
		delete[] art[i];
	}
	delete[] art;
	art = nullptr;
}

unsigned int ASCII::getXLength() {
	return xLength;
}

unsigned int ASCII::getYLength() {
	return yLength;
}

CHAR_INFO** ASCII::getArt() {
	return art;
}

CHAR_INFO ASCII::getArtAtLoc(COORD cord) {
	if (art != nullptr)
		if (cord.X < xLength && cord.Y < yLength) {
			return art[cord.X][cord.Y];
		}
		else {
			return g_errorchar;
		}
	return g_background;
}