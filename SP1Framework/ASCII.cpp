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
		//case etc:
	case HORIZONTAL_ROAD_ART:
		arttxt = "Hroad.txt";
		break;
	case VERTICAL_ROAD_ART:
		arttxt = "Vroad.txt";
		break;
	default:
		arttxt = "NA";
		break;
	}

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
						if (numPixel >= 1)
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
					art[x][y] = pixel;
					numPixel++;
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
		return art[cord.X][cord.Y];
	return g_background;
}