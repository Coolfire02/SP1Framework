#include "Level.h"

void tokenize(std::string const& str, const char delim,
	std::vector<std::string>& out);

bool Level::processKBEvents(SKeyEvent keyEvents[]) {
	bool eventIsProcessed = false;

	//When it is MAINGAME State, if WASD move fire truck.. etc
	if (state == LS_MAINGAME) {
		Map* map = levelspecific_maps.at(state);
		COORD truck_origPos = truck_ptr->getWorldPosition();
		COORD future_pos = truck_origPos;
		if (keyEvents[K_W].keyDown)
			future_pos.Y--;
		if (keyEvents[K_A].keyDown)
			future_pos.X -= 2;
		if (keyEvents[K_S].keyDown)
			future_pos.Y++;
		if (keyEvents[K_D].keyDown)
			future_pos.X += 2;
		if (future_pos.X != truck_origPos.X || future_pos.Y != truck_origPos.Y) {
			if (map->isInRange(future_pos)) {
				eventIsProcessed = true;
				bool canMove = false;
				truck_ptr->setWorldPosition(future_pos);
				for (auto& obj : obj_ptr) {
					if (obj->isCollided(*truck_ptr)) {
						if (obj->getType() == "Forest") {
							canMove = false;
							state = LS_FOREST_SCENE;
							break;
						}
						else if (obj->getType() == "Road") {
							canMove = true;
						}
					}
				}
				//debug to remove
				//canMove = true;
				if(!canMove)
					truck_ptr->setWorldPosition(truck_origPos);
			}
		}
	}
	else if (state == LS_LEVEL_BUILDER) {
		Map* map = levelspecific_maps.at(state);
		COORD mapOffset = map->getMapToBufferOffset();
		if (keyEvents[K_W].keyDown)
			mapOffset.Y -= 10;
		if (keyEvents[K_A].keyDown)
			mapOffset.X -= 10;
		if (keyEvents[K_S].keyDown)
			mapOffset.Y += 5;
		if (keyEvents[K_D].keyDown)
			mapOffset.X += 10;
	}
	// init new stages if state change
	(*this).checkStateChange();
	return eventIsProcessed;
	return true;
}

bool Level::processMouseEvents(SMouseEvent &mouseEvent) {
	bool eventIsProcessed = true;
	if (currently_played_MG_ptr != NULL || state == LS_MAINMENU || state == LS_LEVEL_BUILDER) {
		COORD mousePos = { mouseEvent.mousePosition };
		associatedConsole.writeToBuffer(mousePos.X, mousePos.Y, "ATTACHED");
		switch (mouseEvent.eventFlags) {
		case 0:
			if (mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				
				if (currently_played_MG_ptr != NULL) {
					//minigamehandlemouseevent()...
				}
				else {
					Map* map = levelspecific_maps.at(state);
					switch (state) {
					case LS_MAINMENU:
						//If mouse cursor is touching level obj, start level etc
					case LS_LEVEL_BUILDER:
						//if mouse cursor is touching level obj, clip onto it so u can move it around
						std::map<short, GameObject*> sort;
						for (auto& object_ptr : obj_ptr) {
							if (!object_ptr->isActive()) continue;
							sort.insert(std::pair<short, GameObject*>(object_ptr->getWeight(), object_ptr));
						}
						COORD bufferOffset = map->getMapToBufferOffset();
						if (pickedUp_obj == NULL) {
							Beep(5140, 30);
							//sort from highest weight to lowest allowing u to pickup the "most infront" obj
							std::map<short, GameObject*> ::iterator it;
							for (it = sort.begin(); it != sort.end(); it++) {
								if((*it).second->isInLocation(mousePos.X + bufferOffset.X, mousePos.Y + bufferOffset.Y)) {
									pickedUp_obj = (*it).second;
								}
							}
						}
						else {
							Beep(5140, 30);
							pickedUp_obj->setWorldPosition(mousePos.X+bufferOffset.X, mousePos.Y+bufferOffset.Y);
						}
						
					}
				}
			}
		case DOUBLE_CLICK:
			break;
		case MOUSE_WHEELED:
			break;
		default:
			if (state == LS_LEVEL_BUILDER) {
				delete pickedUp_obj;
				pickedUp_obj == NULL; //No longer holding obj
			}
			break;
		}

		(*this).checkStateChange();
		return eventIsProcessed;
	}
	else {
		eventIsProcessed = false;
	}
	return eventIsProcessed;
}

void Level::renderObjsToMap() {
	if (currently_played_MG_ptr != NULL) {
		//(*currently_played_MG_ptr).renderMGObjsToMap(); TODO
	}
	else {
		switch (state) {
		case LS_LEVEL_BUILDER:
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
			std::map<short, GameObject*> sort;
			for (auto& object_ptr : obj_ptr) {
				if (!object_ptr->isActive()) continue;
				sort.insert(std::pair<short, GameObject*>(object_ptr->getWeight(), object_ptr));
			}
			for (auto& element : sort) {
				for (int x = 0; x < element.second->getXLength(); x++) {
					for (int y = 0; y < element.second->getYLength(); y++) {
						COORD mapLoc = { x + element.second->getWorldPosition().X , y + element.second->getWorldPosition().Y };
						//if this object art at this location is of a g_background, do not overwrite
						if (element.second->getArtAtLoc(x, y).Attributes == g_background.Attributes &&
							element.second->getArtAtLoc(x, y).Char.AsciiChar == g_background.Char.AsciiChar) {
							continue;
						}
						map->setCharAtLoc(mapLoc.X, mapLoc.Y , element.second->getArtAtLoc(x, y));
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
		Map* actualMap = levelspecific_maps.at(state);
		CHAR_INFO** map = actualMap->getMap();
		COORD mapOffset = actualMap->getMapToBufferOffset();
		for (int i = 0; i < g_consoleSize.X; i++) {
			for (int j = 0; j < g_consoleSize.Y; j++) {
				unsigned int worldX = i + mapOffset.X;
				unsigned int worldY = j + mapOffset.Y;
				bool inRangetemp = actualMap->isInRange(worldX, worldY);
				if (actualMap->isInRange(worldX, worldY) == true) 
					associatedConsole.writeToBuffer(i, j, map[worldX][worldY].Char.AsciiChar, map[worldX][worldY].Attributes);
				else 
					associatedConsole.writeToBuffer(i, j, ' ', 0x00);
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


Level::Level(LEVEL level, Console& console) : associatedConsole(console)
{
	originalState = LS_COUNT;
	player_ptr = NULL;
	truck_ptr = NULL;
	currently_played_MG_ptr = NULL;
	state = LS_LEVEL_BUILDER; //TEMPORARY CODE FOR TESTING
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

		std::ifstream file("LEVELS\\"+levelName+".txt");
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
				else if (line_array.at(0) == "FireTruck") {
					GameObject* ptr = truck_ptr;
					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
				}
				else if (line_array.at(0) == "FireStation") {
					GameObject* ptr = new FireStation();
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
			map->setMapToBufferOffset(mapDisplayOffset);
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
	delete pickedUp_obj;
}

//always called at the start of each game loop. Making sure a level state is initialised as per
//requested before its properly handled elsewhere.
void Level::checkStateChange() {
	if (originalState != state) {
		newStageinit();
	}
}

//Whenever there is a state change, if there is any initialization to process, it'll be done here
void Level::newStageinit() {
	if (currently_played_MG_ptr != NULL) {
		FireTruck truck = (*truck_ptr);
		truck.setActive(false);
	}
	else {
		switch (state) {
		case LS_MAINMENU:
			break;
		case LS_MAINGAME:
			player_ptr->setActive(false);
		}
	}
	originalState = state;
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

