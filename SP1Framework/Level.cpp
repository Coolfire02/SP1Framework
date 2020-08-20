#include "Level.h"

void tokenize(std::string const& str, const char delim,
	std::vector<std::string>& out);

void Level::renderObjsToMap() {
	if (currently_played_MG_ptr != NULL) {
		//(*currently_played_MG_ptr).renderMGObjsToMap(); TODO
	}
	else {
		switch (state) {
		case LS_MAINGAME:
			/*Main game should consist of:
			Fire Station
			Fire Truck
			Fire Fighter
			All Minigames
			Roads
			Forest Object*/

			Map* map = levelspecific_maps[state];
			map->clearMap();
			//Rendering all characters collected in the Object_ptr vector to map. 
			for (auto& object_ptr : obj_ptr) {
				for (int x = 0; x < object_ptr->getXLength(); x++) {
					for (int y = 0; y < object_ptr->getYLength(); y++) {
						map->setCharAtLoc(x+object_ptr->getWorldPosition().X, y+object_ptr->getWorldPosition().Y, object_ptr->getArtAtLoc(x, y));
					}
				}
			}


		//and all other cases that are not minigames TODO
		}
	}
}

void Level::renderMap() {
	if (currently_played_MG_ptr != NULL) {
		//(*currently_played_MG_ptr).render(); TODO
	}
	else {
		CHAR_INFO** map = levelspecific_maps.at(state)->getMap();
		COORD mapOffset = levelspecific_maps.at(state)->getMapToBufferOffset();
		for (int i = 0; i < g_consoleSize.X; i++) {
			for (int j = 0; j < g_consoleSize.Y; j++) {
				unsigned int worldX = i + mapOffset.X;
				unsigned int worldY = j + mapOffset.Y;
				associatedConsole.writeToBuffer(i, j, map[worldX][worldY].Char.AsciiChar, map[worldX][worldY].Attributes);
			}
		}
	}
}

bool Level::setState(LEVELSTATE state) {
	if (std::find(levelStates.begin(), levelStates.end(), state) != levelStates.end()) {
		(*this).state = state;
		return true;
	}
	return false; //not a state that exists in level
}


Level::Level(LEVEL level, Console &console) : associatedConsole(console)
{
	player_ptr = NULL;
	truck_ptr = NULL;
	currently_played_MG_ptr = NULL;
	state = LS_MAINGAME; //TEMPORARY CODE FOR TESTING
	COORD mainDisplayOrigin = { 0,0 };
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
				
				std::vector<std::string> line_array;

				for (auto& line : out) {
					line_array.push_back(line);
				}

				if (line_array.at(0) == "MapSize") {
					mainMapSize.X = std::stoi(line_array.at(1));
					mainMapSize.Y = std::stoi(line_array.at(2));
				}
				else if (line_array.at(0) == "DisplayOrigin") {
					mainDisplayOrigin.X = std::stoi(line_array.at(1));
					mainDisplayOrigin.Y = std::stoi(line_array.at(2));
				}
				else if (line_array.at(0) == "FireMan") {
					GameObject* ptr = player_ptr;
					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
				}
				else if (line_array.at(0) == "FireStation") {
					GameObject* ptr = new FireStation();
					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
				}
				else if (line_array.at(0) == "FireTruck") {
					GameObject* ptr = new FireTruck();
					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
				}
				else if (line_array.at(0) == "MiniGame_WL") {
					MiniGame* ptr = new MiniGame_WL();
					
					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
					mg_ptr.push_back(ptr);

					levelStates.push_back(LS_MINIGAME_WL);
				}
				else if (line_array.at(0) == "ROAD") {
					GameObject* ptr = new Road();
					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
				}
			}
		}
	}
	
	//map_ptrs = new Map[levelStates.size()]();

	for (unsigned int i = 0; i < levelStates.size(); i++) {
		bool add = true;
		COORD mapSize = { 213,50 };
		COORD mapDisplayOffset{ 0,0 };
		switch (levelStates[i]) {
		case MAINMENU: mapSize = { 1000,50 }; break;
		case LS_BEGIN_SCENE: mapSize = { 213,50 }; break;

		case LS_LEVEL_BUILDER:
		case LS_MAINGAME: 
			mapSize = mainMapSize; 
			mapDisplayOffset = mainDisplayOrigin;
			break;
		

		//Minigame maps to be accessed when LS_STATE is Minigame, render from Minigame class.
		//case LS_MINIGAME_WL:
		//case LS_MINIGAME_BHOS:
		//	for (auto& entry : mg_ptr) {
		//		if (entry->getAssociatedLSState() == levelStates[i]) {
		//			mapSize = entry->getMapSize();
		//		}
		//	}
		//	break;

		case LS_FOREST_SCENE: mapSize = { 213, 50 }; break;
		case LS_END_SCENE: mapSize = { 213, 50 }; break;
		default:
			add = false;
		}
		if (add) {
			Map* map = new Map(mapSize.X, mapSize.Y);
			levelspecific_maps.insert({ levelStates[i], map });
		}
	}
}

Level::~Level()
{
	for (auto& element : obj_ptr) { //deletes all pointers created under the level
		delete element;
	}
	delete currently_played_MG_ptr;
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

