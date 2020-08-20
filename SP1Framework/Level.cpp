#include "Level.h"

void tokenize(std::string const& str, const char delim,
	std::vector<std::string>& out);

Level::Level(LEVEL level)
{
	player_ptr = NULL;
	truck_ptr = NULL;
	state = LS_COUNT;
	displayOrigin = { 0,0 };
	COORD mainMapSize = { 213,50 };
	(*this).level = level;
	
	if (level == MAINMENU) {
		state = LS_MAINMENU;
		levelStates.push_back(LS_MAINMENU);
	}
	else {
		std::string levelName;
		switch (level) {
		case TUTORIAL: levelName = "TUTORIAL"; break;
		case STAGE_1_LEVEL_1: levelName = "STAGE_1_LEVEL_1"; break;
		case STAGE_2_LEVEL_1: levelName = "STAGE_2_LEVEL_1"; break;
		default: levelName = "UNKNOWN";
		}

		levelStates.push_back(LS_BEGIN_SCENE);
		levelStates.push_back(LS_MAINGAME);
		levelStates.push_back(LS_FOREST_SCENE);
		levelStates.push_back(LS_END_SCENE);

		if (devMode)
			levelStates.push_back(LS_LEVEL_BUILDER);

		player_ptr = new Player();
		truck_ptr = new FireTruck();

		obj_ptr.push_back(player_ptr);
		obj_ptr.push_back(truck_ptr);

		std::ifstream file(levelName+".txt");
		std::string line;
		if (file.is_open()) {
			int split;
			std::string varType;
			while (std::getline(file, line)) {
				split = 0;
				std::vector<std::string> out;
				tokenize(line, ',', out);
				
				size_t lineCommas = std::count(line.begin(), line.end(), ',');
				std::string* line_array = new std::string[lineCommas];

				for (auto& line : out) {
					line_array[split] = line;
					split++;
				}

				if (line_array[0] == "MapSize") {
					mainMapSize.X = std::stoi(line_array[1]);
					mainMapSize.Y = std::stoi(line_array[2]);
				}
				else if (line_array[0] == "DisplayOrigin") {
					displayOrigin.X = std::stoi(line_array[1]);
					displayOrigin.X = std::stoi(line_array[2]);
				}
				else if (line_array[0] == "FireStation") {
					GameObject* ptr = new FireStation();
					ptr->setWorldPosition(std::stoi(line_array[1]), std::stoi(line_array[2]));
					obj_ptr.push_back(ptr);
				}
				else if (line_array[0] == "FireTruck") {
					GameObject* ptr = new FireTruck();
					ptr->setWorldPosition(std::stoi(line_array[1]), std::stoi(line_array[2]));
					obj_ptr.push_back(ptr);
				}
				else if (line_array[0] == "MiniGame_WL") {
					MiniGame* ptr = new MiniGame_WL();
					
					ptr->setWorldPosition(std::stoi(line_array[1]), std::stoi(line_array[2]));
					obj_ptr.push_back(ptr);
					mg_ptr.push_back(ptr);

					levelStates.push_back(LS_MINIGAME_WL);
				}
				else if (line_array[0] == "ROAD") {
					GameObject* ptr = new Road();
					ptr->setWorldPosition(std::stoi(line_array[1]), std::stoi(line_array[2]));
					obj_ptr.push_back(ptr);
				}
				delete[] line_array;
			}
		}
	}
	
	//map_ptrs = new Map[levelStates.size()]();
	for (unsigned int i = 0; i < levelStates.size(); i++) {
		COORD mapSize = { 213,50 };
		switch (levelStates[i]) {
		case MAINMENU: mapSize = { 1000,50 }; break;
		case LS_BEGIN_SCENE: mapSize = { 213,50 }; break;

		case LS_LEVEL_BUILDER:
		case LS_MAINGAME: 
			mapSize = mainMapSize; break;

		case LS_MINIGAME_WL:
		case LS_MINIGAME_BHOS:
			for (auto& entry : mg_ptr) {
				if (entry->getAssociatedLSState() == levelStates[i]) {
					mapSize = entry->getMapSize();
				}
			}
			break;

		case LS_FOREST_SCENE: mapSize = { 213, 50 }; break;
		case LS_END_SCENE: mapSize = { 213, 50 }; break;
		}
	}
}

Level::~Level()
{
	for (auto& element : obj_ptr) { //deletes all pointers created under the level
		delete element;
	}
	for (auto& entry : map_ptrs) {
		delete entry.second;
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
