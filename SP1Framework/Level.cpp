#include "Level.h"

void tokenize(std::string const& str, const char delim,
	std::vector<std::string>& out);

Level::Level(LEVEL level)
{
	player_ptr = nullptr;
	truck_ptr = nullptr;
	mg_ptr = nullptr;
	state = LS_COUNT;
	displayOrigin = { 0,0 };
	COORD mapSize = { (int) map.getXLength(), (int) map.getYLength() };
	(*this).level = level;
	
	if (level == MAINMENU) {
		state = LS_MAINMENU;
	}
	else {
		string levelName;
		switch (level) {
		case MAINMENU: levelName = "MAINMENU"; break;
		case TUTORIAL: levelName = "TUTORIAL"; break;
		case STAGE_1_LEVEL_1: levelName = "STAGE_1_LEVEL_1"; break;
		case STAGE_2_LEVEL_1: levelName = "STAGE_2_LEVEL_1"; break;
		default: levelName = "UNKNOWN";
		}

		player_ptr = new Player();
		truck_ptr = new FireTruck();

		obj_ptr.push_back(player_ptr);
		obj_ptr.push_back(truck_ptr);

		ifstream file(levelName+".txt");
		string line;
		if (file.is_open()) {
			int split;
			string varType;
			while (getline(file, line)) {
				split = 0;
				vector<string> out;
				tokenize(line, ',', out);
				
				size_t lineCommas = count(line.begin(), line.end(), ',');
				string* line_array = new string[lineCommas];

				for (auto& line : out) {
					line_array[split] = line;
					split++;
				}

				if (line_array[0] == "MapSize") {
					mapSize.X = stoi(line_array[1]);
					mapSize.Y = stoi(line_array[2]);
				}
				else if (line_array[0] == "DisplayOrigin") {
					displayOrigin.X = stoi(line_array[1]);
					displayOrigin.X = stoi(line_array[2]);
				}
				else if (line_array[0] == "FireStation") {
					GameObject* ptr = new FireStation();
					ptr->setWorldPosition(stoi(line_array[1]), stoi(line_array[2]));
					obj_ptr.push_back(ptr);
				}
				else if (line_array[0] == "FireTruck") {
					GameObject* ptr = new FireTruck();
					ptr->setWorldPosition(stoi(line_array[1]), stoi(line_array[2]));
					obj_ptr.push_back(ptr);
				}
				else if (line_array[0] == "MiniGame_WL") {
					GameObject* ptr = new MiniGame_WL();
					ptr->setWorldPosition(stoi(line_array[1]), stoi(line_array[2]));
					obj_ptr.push_back(ptr);
				}
				else if (line_array[0] == "ROAD") {
					GameObject* ptr = new Road();
					ptr->setWorldPosition(stoi(line_array[1]), stoi(line_array[2]));
					obj_ptr.push_back(ptr);
				}
				delete[] line_array;
			}
		}

		if (map.getXLength() != mapSize.X || map.getYLength() != mapSize.Y) {
			map.setSize(mapSize.X, mapSize.Y);
		}

	}
}

Level::~Level()
{
	for (auto& element : obj_ptr) { //deletes all pointers created under the level
		delete element;
	}
}

void tokenize(std::string const& str, const char delim,
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
