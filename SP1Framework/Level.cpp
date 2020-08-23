#include "Level.h"

void tokenize(std::string const& str, const char delim,
	std::vector<std::string>& out);

void Level::gameLoopListener() {
	if (currently_played_MG_ptr != NULL) {
		if (currently_played_MG_ptr->isCompleted()) 
		{
			// if minigame is completed, delete it from mg_ptr but keep in obj_ptr
			// this is so that the minigame still exists in the level, but can no longer be played further
			for (auto& pointer : mg_ptr) {
				pointer == currently_played_MG_ptr;
				pointer = nullptr;
			}
			mg_ptr.erase(std::remove(mg_ptr.begin(), mg_ptr.end(), nullptr), mg_ptr.end()); //Removes all nullptrs from vector

			// TODO adding of money and water
			currently_played_MG_ptr = NULL;
			state = LS_MAINGAME;
			(*this).checkStateChange();
		}
		else // Minigame not completed proceeding to call Game Loop Listener of Minigame
		{
			currently_played_MG_ptr->gameLoopListener();
		}
	}
}

bool Level::processKBEvents(SKeyEvent keyEvents[]) {
	bool eventIsProcessed = false;

	if (currently_played_MG_ptr != NULL) {
		currently_played_MG_ptr->processKBEvents(keyEvents);
	}
	else {
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
							bool stopLoop = false;
							std::string type = obj->getType();
							if (type == "FireTruck") continue;

							//Interaction Handling between truck & other objs
							if (type == "Forest") {
								canMove = false;
								state = LS_FOREST_SCENE;
								
								stopLoop = true;
							}

							else if (type == "MiniGame_RM") {
								for (auto& minigame_ptr : mg_ptr) {
									if (minigame_ptr->getType() == "MiniGame_RM") {
										currently_played_MG_ptr = minigame_ptr;
										currently_played_MG_ptr->start();
										state = LS_MINIGAME_RM;
										break;
									}
								}
								canMove = false;
								stopLoop = true;
							}

							else if (type.rfind("Road") != std::string::npos) {
								canMove = true;
							}

							if (stopLoop)
								break;
						}
					}
					//debug to remove
					//canMove = true;
					if (!canMove)
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
			if (keyEvents[K_S].keyDown) {
				if (keyEvents[K_W].keyDown) {
					if (state == LS_LEVEL_BUILDER) {
						saveLevel();
						return true;
					}
				}
				mapOffset.Y += 5;
			}
			if (keyEvents[K_D].keyDown)
				mapOffset.X += 10;
			map->setMapToBufferOffset(mapOffset);
		}
		// init new stages if state change
	}
	(*this).checkStateChange();
	return eventIsProcessed;
}

bool Level::processMouseEvents(SMouseEvent &mouseEvent) {
	bool eventIsProcessed = true;
	if (currently_played_MG_ptr != NULL || state == LS_MAINMENU || state == LS_LEVEL_BUILDER) {

		if (currently_played_MG_ptr != NULL) {
			currently_played_MG_ptr->processMouseEvents(mouseEvent);
		}
		else {
			COORD mousePos = { mouseEvent.mousePosition };

			// if left-mouse is currently being pressed
			if (mouseEvent.buttonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
				switch (state) {
				case LS_MAINMENU:
					break;
				case LS_LEVEL_BUILDER:
					if (currently_played_MG_ptr == NULL) {
						if (pickedUp_obj != NULL) {
							Map* map = levelspecific_maps.at(state);
							COORD bufferOffset = map->getMapToBufferOffset();
							pickedUp_obj->setWorldPosition(mousePos.X + bufferOffset.X, mousePos.Y + bufferOffset.Y);
						}
					}
				}
			}
			else {
				if (pickedUp_obj != NULL)
					pickedUp_obj = NULL;
			}


			switch (mouseEvent.eventFlags) {
			case 0:
				if (mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED) { //If clicked
					if (FROM_LEFT_1ST_BUTTON_PRESSED != 0) {
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
								std::multimap<short, GameObject*> sort;
								for (auto& object_ptr : obj_ptr) {
									if (!object_ptr->isActive()) continue;
									sort.insert(std::pair<short, GameObject*>(object_ptr->getWeight() * (-1), object_ptr));
								}
								COORD bufferOffset = map->getMapToBufferOffset();
								if (pickedUp_obj == NULL) {
									//Beep(5140, 30);
									//sort from highest weight to lowest allowing u to pickup the "most infront" obj
									for (auto element : sort) {
										COORD cursorPos = { mousePos.X + bufferOffset.X, mousePos.Y + bufferOffset.Y };
										if (element.second->isInLocation(cursorPos)) {
											pickedUp_obj = element.second;
											//pickedUp_obj->setWorldPosition(mousePos.X + bufferOffset.X, mousePos.Y + bufferOffset.Y);
											break;
										}
									}
								}
							}
						}
					}

				}
				else if (FROM_LEFT_1ST_BUTTON_PRESSED == 0) {
					if (state == LS_LEVEL_BUILDER) {
						pickedUp_obj == NULL; //No longer holding obj
					}
				}
			case DOUBLE_CLICK:
				break;
			case MOUSE_WHEELED:
				break;
			default:
				break;
			}
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
		currently_played_MG_ptr->renderObjsToMap();
	}
	else {
		switch (state) {
		case LS_LEVEL_BUILDER:
		case LS_MAINGAME:
			/*
			LS_MAINGAME objects:
			Fire Station
			Fire Truck
			Fire Fighter
			All Minigames
			Roads
			Forest Object
			*/

			Map* map = levelspecific_maps[state];
			map->clearMap();
			//Rendering all characters collected in the Object_ptr vector to map. 
			std::multimap<short, GameObject*> sort;
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
		currently_played_MG_ptr->renderMap();
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
	state = LS_MAINGAME; //TEMPORARY CODE FOR TESTING
	COORD mainDisplayOrigin = { 0,0 };
	COORD mainMapSize = { 213,50 };
	(*this).level = level;
	
	if (level == MAINMENU) {
		state = LS_MAINMENU;
		levelStates.push_back(LS_MAINMENU);
	}
	else {
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
				else if (line_array.at(0) == "MiniGame_RM") {
					MiniGame* ptr = new MiniGame_RM(level, console);
					levelStates.push_back(ptr->getAssociatedLSState());

					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
					mg_ptr.push_back(ptr);
				}
				else if (line_array.at(0) == "Vertical_Road") {
					ROADTYPE type = R_VERTICAL;
					GameObject* ptr = new Road(type);
					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
				}
				else if (line_array.at(0) == "Horizontal_Road") {
					ROADTYPE type = R_HORIZONTAL;
					GameObject* ptr = new Road(type);
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
	if (originalState == LS_MAINGAME) {
		if (currently_played_MG_ptr != NULL) {
			for (auto& objs : obj_ptr) {
				objs->setActive(false);
			}
		}
	}
	else {
		switch (state) {
		case LS_MAINMENU:
			for (auto& objs : obj_ptr) {
				objs->setActive(false);
			}
			break;
		case LS_MAINGAME:
			for (auto& objs : obj_ptr) {
				objs->setActive(true);
			}
			player_ptr->setActive(false);
		}
	}
	originalState = state;
}

void Level::saveLevel() {
	std::ofstream file("LEVELS\\" + levelName + ".txt");
	Map* mainMap = levelspecific_maps.at(LS_MAINGAME);
	COORD MapSize = { mainMap->getXLength(), mainMap->getYLength() };
	COORD DisplayOrigin = mainMap->getMapToBufferOffset();
	file << "MapSize," << MapSize.X << "," << MapSize.Y << std::endl;
	file << "DisplayOrigin," << DisplayOrigin.X << "," << DisplayOrigin.Y << std::endl;
	std::multimap<short, GameObject*> sort;
	for (auto& object_ptr : obj_ptr) {
		sort.insert(std::pair<short, GameObject*>(object_ptr->getWeight()*(-1), object_ptr));
	}
	for (auto& element : sort) {
		file << element.second->getType() << "," << element.second->getWorldPosition().X << "," << element.second->getWorldPosition().Y << std::endl;
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

