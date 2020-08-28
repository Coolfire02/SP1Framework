#include "Level.h"

void tokenize(std::string const& str, const char delim, std::vector<std::string>& out);

void Level::gameLoopListener() {
	if (currently_played_MG_ptr != NULL) {
		if (currently_played_MG_ptr->isCompleted())
		{
			// if minigame is completed, delete it from mg_ptr but keep in obj_ptr
			// this is so that the minigame still exists in the level, but can no longer be played further
			for (auto& pointer : mg_ptr) {
				if (pointer == currently_played_MG_ptr) {
					pointer = nullptr;
				}
			}
			mg_ptr.erase(std::remove(mg_ptr.begin(), mg_ptr.end(), nullptr), mg_ptr.end()); //Removes all nullptrs from vector

			// TODO adding of money and water
			player_ptr->receiveMoney(currently_played_MG_ptr->getMoneyEarned());
			truck_ptr->FillWater(currently_played_MG_ptr->getWaterCollected());
			
			Money_ptr->setText(getMoneyBalancePrefix());
			ft_waterCollected_text->setText(getTruckWaterPrefix());

			ft_waterCollected->setProgress((truck_ptr->getCurrentWaterLevel() / truck_ptr->getMaxWater()) * 100);

			currently_played_MG_ptr = NULL;
			state = LS_MAINGAME;
			(*this).checkStateChange();
		}
		else // Minigame not completed proceeding to call Game Loop Listener of Minigame
		{
			currently_played_MG_ptr->gameLoopListener();
		}
	}
	//If mouse cursor is touching level obj, start level etc
	
}

bool Level::processKBEvents(SKeyEvent keyEvents[]) {
	bool eventIsProcessed = false;

	if (currently_played_MG_ptr != NULL) {
		currently_played_MG_ptr->processKBEvents(keyEvents);
	}
	else {
		if (state == LS_MAINMENU) {
			Map* map = levelspecific_maps.at(state);
			COORD player_origPos = player_ptr->getWorldPosition();
			COORD future_pos = player_origPos;
			if (keyEvents[K_W].keyDown)
				future_pos.Y--;
			if (keyEvents[K_A].keyDown)
				future_pos.X -= 2;
			if (keyEvents[K_S].keyDown)
				future_pos.Y++;
			if (keyEvents[K_D].keyDown)
				future_pos.X += 2;
			if ((future_pos.X != player_origPos.X || future_pos.Y != player_origPos.Y) && map->isInRange(future_pos)) {
				player_ptr->setWorldPosition(future_pos);
				if (player_ptr->getWorldPosition().X - map->getMapToBufferOffset().X > 183) {
					COORD newMapOffset = { player_ptr->getWorldPosition().X - 183, 0 };
					if (map->isInRange(newMapOffset.X + g_consoleSize.X - 1, newMapOffset.Y + g_consoleSize.Y - 1))
						map->setMapToBufferOffset(newMapOffset);
				}
				else if (player_ptr->getWorldPosition().X - map->getMapToBufferOffset().X < 30) {
					COORD newMapOffset = { player_ptr->getWorldPosition().X - 31, 0 };
					map->setMapToBufferOffset(newMapOffset);
				}
				bool canMove = false;
				for (auto& obj : stages_ptr) {
					if (obj->isCollided(*player_ptr)) {
						nextLevel = obj->getStage();
						player_ptr->setWorldPosition(4, 45);
						COORD cord = { 0,0 };
						map->setMapToBufferOffset(cord);
						eventIsProcessed = true;
					}
				}
			}
		}

		else if (state == LS_MAINGAME) {
			Map* map = levelspecific_maps.at(state);
			COORD truck_origPos = truck_ptr->getWorldPosition();
			COORD future_pos = truck_origPos;
			if (keyEvents[K_W].keyDown)
				future_pos.Y--;
			if (keyEvents[K_A].keyDown)
			{
				future_pos.X -= 2;
				truck_ptr->setDirection(T_LEFT);
			}
			if (keyEvents[K_S].keyDown)
				future_pos.Y++;
			if (keyEvents[K_D].keyDown)
			{
				future_pos.X += 2;
				truck_ptr->setDirection(T_RIGHT);
			}
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
								//state = LS_FOREST_SCENE;
								fire -= truck_ptr->getCurrentWaterLevel();
								truck_ptr->setWaterLevel(0);

								(*this).updateProgressDisplays();	

								if (fire <= 0) {
									fire = 0;
									//GAME END TODO
								}
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

							else if (type == "MiniGame_WL") {
								for (auto& minigame_ptr : mg_ptr) {
									if (minigame_ptr->getType() == "MiniGame_WL") {
										currently_played_MG_ptr = minigame_ptr;
										currently_played_MG_ptr->start();
										state = LS_MINIGAME_WL;
										break;
									}
								}
								canMove = false;
								stopLoop = true;
							}

							else if (type == "MiniGame_BHOS") {
								for (auto& minigame_ptr : mg_ptr) {
									if (minigame_ptr->getType() == "MiniGame_BHOS") {
										currently_played_MG_ptr = minigame_ptr;
										currently_played_MG_ptr->start();
										state = LS_MINIGAME_BHOS;
										break;
									}
								}
								canMove = false;
								stopLoop = true;
							}

							else if (type == "MiniGame_RW") {
								for (auto& minigame_ptr : mg_ptr) {
									if (minigame_ptr->getType() == "MiniGame_RW") {
										currently_played_MG_ptr = minigame_ptr;
										currently_played_MG_ptr->start();
										state = LS_MINIGAME_RW;
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
				COORD mapOffset = { truck_ptr->getWorldPosition().X - g_consoleSize.X / 2 + 10 , truck_ptr->getWorldPosition().Y - g_consoleSize.Y / 2 - 2 };
				map->setMapToBufferOffset(mapOffset);
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
					//Beep(5500, 50);
					if (state == LS_LEVEL_BUILDER) {
						saveLevel();
						return true;
					}
				}
				mapOffset.Y += 5;
			}
			if (keyEvents[K_C].keyReleased) {
				if (keyEvents[K_CTRL].keyDown) {
					if (pickedUp_obj != NULL) {
						//pickedUp_obj = (*pickedUp_obj)
					}
				}
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

bool Level::processMouseEvents(SMouseEvent& mouseEvent) {
	bool eventIsProcessed = false;
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
						COORD bufferOffset = map->getMapToBufferOffset();
						switch (state) {
						case LS_MAINGAME: {
							std::multimap<short, GameObject*> sort;
							for (auto& object_ptr : obj_ptr) {
								if (!object_ptr->isActive()) continue;
								sort.insert(std::pair<short, GameObject*>(object_ptr->getWeight() * (-1), object_ptr));
							}
							for (auto element : sort) {
								if (element.second->hasRelativePos()) {
									COORD cursorPos = mousePos;
									if (element.second->isInRelativeLocation(cursorPos)) {
										if (element.second->getType() == "Shop") {
											state = LS_GAMESHOP;
											(*this).checkStateChange();
											break;
										}
									}
								}
								else {
									COORD cursorPos = { mousePos.X + bufferOffset.X, mousePos.Y + bufferOffset.Y };
									if (element.second->isInLocation(cursorPos)) {
										// nothing 
									}
								}
							}
							break;
						}

						case LS_LEVEL_BUILDER: {
							//if mouse cursor is touching level obj, clip onto it so u can move it around
							std::multimap<short, GameObject*> sort;
							for (auto& object_ptr : obj_ptr) {
								if (!object_ptr->isActive()) continue;
								sort.insert(std::pair<short, GameObject*>(object_ptr->getWeight() * (-1), object_ptr));
							}

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

			}
			else if (FROM_LEFT_1ST_BUTTON_PRESSED == 0) {
				if (state == LS_LEVEL_BUILDER) {
					pickedUp_obj = NULL; //No longer holding obj
				}
			}
			break;
		case DOUBLE_CLICK: {
			Map* map = levelspecific_maps.at(state);
			COORD bufferOffset = map->getMapToBufferOffset();
			switch (state) {
			case LS_GAMESHOP:
			{
				std::multimap<short, GameObject*> sort;
				for (auto& object_ptr : shop_obj_ptr) {
					if (!object_ptr->isActive()) continue;
					sort.insert(std::pair<short, GameObject*>(object_ptr->getWeight() * (-1), object_ptr));
				}
				for (auto element : sort) {
					if (element.second->hasRelativePos()) {
						COORD cursorPos = mousePos;
						if (element.second->isInRelativeLocation(cursorPos)) {
							// intentionally left blank
						}
					}
					else {
						COORD cursorPos = { mousePos.X + bufferOffset.X, mousePos.Y + bufferOffset.Y };
						if (element.second->isInLocation(cursorPos) && element.second->getType() == "ShopItem") {
							// GameShop item purchasing
							ShopItem* shopItem = dynamic_cast<ShopItem*>(element.second);
							if (player_ptr->getMoney() >= shopItem->getCost()) {
								player_ptr->spendMoney(shopItem->getCost());
								(*this).updateProgressDisplays();
								Beep(8000, 50);
								player_ptr->getInventory().addItem(shopItem->getItem());
							}

							// eventIsProcessed to true to add a 1s cooldown
							eventIsProcessed = true;
							break;
						}
					}
				}
				// switch break
				break;
			}
			}
			break;
		}
		case MOUSE_WHEELED:
			break;
		default:
			break;
		}
	}
	(*this).checkStateChange();
	return eventIsProcessed;
}

void Level::renderObjsToMap() {
	if (currently_played_MG_ptr != NULL) {
		currently_played_MG_ptr->renderObjsToMap();
	}
	else {
		Map* map = levelspecific_maps.at(state);
		switch (state) {
		case LS_MAINMENU:
		case LS_LEVEL_BUILDER:
		case LS_MAINGAME:
		case LS_GAMESHOP:
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
						if (element.second->hasRelativePos()) {
							mapLoc = { (short)(x + element.second->getRelativePos().X + map->getMapToBufferOffset().X) , (short)(y + element.second->getRelativePos().Y + map->getMapToBufferOffset().Y) };
						}

						//if this object art at this location is of a g_background, do not overwrite
						if (element.second->getArtAtLoc(x, y).Attributes == g_background.Attributes &&
							element.second->getArtAtLoc(x, y).Char.AsciiChar == g_background.Char.AsciiChar) {
							continue;
						}
						map->setCharAtLoc(mapLoc.X, mapLoc.Y, element.second->getArtAtLoc(x, y));
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

Level::Level(LEVEL level, Console& console) : associatedConsole(console), originalTotalFire(100 * level)
{
	// Fire setting
	fire = originalTotalFire;

	originalState = LS_COUNT;
	player_ptr = NULL;
	truck_ptr = NULL;
	Money_ptr = NULL;
	ft_waterCollected = NULL;
	level_progress = NULL;
	currently_played_MG_ptr = NULL;
	if (level == MAINMENU)
		state = LS_MAINMENU;
	else {
		state = LS_MAINGAME; //By changing this to LS_LEVEL_BUILDER (This allows us to set up the map)
	}
	COORD mainDisplayOrigin = { 0,0 };
	COORD mainMapSize = { 213,50 };
	(*this).level = level;
	nextLevel = level;

	player_ptr = new Player();
	obj_ptr.push_back(player_ptr);

	if (level == MAINMENU) {
		state = LS_MAINMENU;
		levelStates.push_back(LS_MAINMENU);
		
		ArtObject* wildFireIcon = new ArtObject(WILDFIRE_TITLE_ART, 1600, "WildFire");
		Text* text = new Text("Stages can be found ->", 0xE0);

		player_ptr->setWorldPosition(4, 45);
		text->setWorldPosition(COORD({ (short)(g_consoleSize.X / 2 - text->getText().size() / 2),(short) g_consoleSize.Y / 2 }));
		wildFireIcon->setWorldPosition(COORD({ (short)(g_consoleSize.X / 2 - wildFireIcon->getXLength() / 2), (short)(g_consoleSize.Y / 2 - wildFireIcon->getYLength()/2) - 7 }));

		Stage* TUTORIAL = new Stage(LEVEL::TUTORIAL);
		Stage* STAGE_1_LEVEL_1 = new Stage(LEVEL::STAGE_1_LEVEL_1);
		Stage* STAGE_2_LEVEL_1 = new Stage(LEVEL::STAGE_2_LEVEL_1);

		obj_ptr.push_back(wildFireIcon);
		obj_ptr.push_back(text);
		obj_ptr.push_back(TUTORIAL);
		obj_ptr.push_back(STAGE_1_LEVEL_1);
		obj_ptr.push_back(STAGE_2_LEVEL_1);

		stages_ptr.push_back(TUTORIAL);
		stages_ptr.push_back(STAGE_1_LEVEL_1);
		stages_ptr.push_back(STAGE_2_LEVEL_1);

		COORD worldCordAssignment = { 213, 16 };
		for (auto& stages : obj_ptr) {
			if (stages->getType() == "Stage") {
				if (worldCordAssignment.X % 213 == 0)
					worldCordAssignment.X += 10;
				stages->setWorldPosition(worldCordAssignment);

				worldCordAssignment.X = worldCordAssignment.X + (short)67;
			}
		}
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
		levelStates.push_back(LS_GAMESHOP);
		levelStates.push_back(LS_FOREST_SCENE);
		levelStates.push_back(LS_END_SCENE);

		if (devMode)
			levelStates.push_back(LS_LEVEL_BUILDER);

		COORD cord = { 0,1 };
		truck_ptr = new FireTruck(100);

		Money_ptr = new Text(getMoneyBalancePrefix());
		ft_waterCollected_text = new Text(getTruckWaterPrefix(), 0xB0);
		level_progress_text = new Text(getFireRemainingPrefix(), 0xC0);
		ft_waterCollected = new ProgressBar(B_HORIZONTAL, 20, 3, 0x70, 0x30);
		level_progress = new ProgressBar(B_HORIZONTAL, 20, 3, 0x70, 0x40);

		Money_ptr->setRelativePos(cord);
		ft_waterCollected->setRelativePos(cord.X, cord.Y + 1);
		level_progress->setRelativePos(cord.X, cord.Y + 4);
		ft_waterCollected_text->setRelativePos(cord.X + 1 + ft_waterCollected->getXLength(), cord.Y + 2);
		level_progress_text->setRelativePos(cord.X + 1 + level_progress->getXLength(), cord.Y + 5);

		ft_waterCollected->setProgress(0);
		level_progress->setProgress(100);

		obj_ptr.push_back(truck_ptr);
		obj_ptr.push_back(Money_ptr);
		obj_ptr.push_back(ft_waterCollected);
		obj_ptr.push_back(level_progress);
		obj_ptr.push_back(ft_waterCollected_text);
		obj_ptr.push_back(level_progress_text);

		//Power Ups

		//Game shop code
		ArtObject* button = new ArtObject(SHOP_ART, 1500, "Shop");
		obj_ptr.push_back(button);
		button->setRelativePos(190, 30);

<<<<<<< HEAD
=======
		ShopItem* item = new ShopItem(Item(ABILITY_ZOOM, 1, "1x Ability Zoom"), 25);
		Text* text = new Text(item->getItem().getDisplayName()+"\ntttt\naaaa", 0xAF);
>>>>>>> c603a4f06719b512ba81c875d2a425b3fc550889

		for (int t = 0; t < TOTAL_SHOP_ITEMS; t++)
		{
			int X_COORD[5] = {15, 55, 95, 135, 175},x = 0, y = 5; //Coord of first row items in shop
			WORD ShopText = 0x70;
			enum ITEMTYPE type;
			std::string ItemName;
			int quantity, price;
			int text_Y_displacement = 5;

			switch (t)
			{
			case(ABILITY_ZOOM):
				type = ABILITY_ZOOM;
				ItemName = "Zoom Ability";
				quantity = 1;
				price = 25;
				x = X_COORD[0];
				y += 0;
				break;

			case(ABILITY_HOMEBASE):
				type = ABILITY_HOMEBASE;
				ItemName = "Homebase Teleportation Ability";
				quantity = 1;
				price = 25;
				x = X_COORD[1];
				y += 0;
				break;

			case(ABILITY_ROADREPAIR):
				type = ABILITY_ROADREPAIR;
				ItemName = "Road Repair Ability";
				quantity = 1;
				price = 25;
				x = X_COORD[2];
				y += 0;
				break;

			case(ABILITY_UNLOCKMG):
				type = ABILITY_UNLOCKMG;
				ItemName = "One-time MiniGame Unlock Ability";
				quantity = 3;
				price = 25;
				x = X_COORD[3];
				y += 0;
				break;

			case(HOSE_HOLY_WATER):
				type = HOSE_HOLY_WATER;
				ItemName = "Hose of Holy Variation";
				quantity = 1;
				price = 200;
				x = X_COORD[4];
				y += 0;
				break;

			case(HOSE_MONEY_SALVAGER):
				type = HOSE_MONEY_SALVAGER;
				ItemName = "Hose of Money Salvage Variation";
				quantity = 1;
				price = 300;
				x = X_COORD[0];
				y *= 3;
				break;

			case(HOSE_ABSORBER):
				type = HOSE_ABSORBER;
				ItemName = "Hose of Absorb Variation";
				quantity = 1;
				price = 450;
				x = X_COORD[1];
				y *= 3;
				break;

			case(HOSE_MAGICAL_WATER):
				type = HOSE_MAGICAL_WATER;
				ItemName = "Hose of Magic Variation";
				quantity = 1;
				price = 1200;
				x = X_COORD[2];
				y *= 3;
				break;

			case(HOSE_MONEY_DUPLICATOR):
				type = HOSE_MONEY_DUPLICATOR;
				ItemName = "Hose of Money Duplication Variation";
				quantity = 1;
				price = 1200;
				x = X_COORD[3];
				y *= 3;
				break;

			default:
				type = ABILITY_ZOOM;
				ItemName = "";
				quantity = 0;
				price = 0;
				x = 0;
				y = 0;
				break;
			}

			ShopItem* item = new ShopItem(Item(type, quantity, (std::to_string(quantity) + " x " + ItemName)), price);
			Text* text = new Text(item->getItem().getDisplayName(), ShopText);
			int txtXPos;
			if (text->getText().length() / 2 < 11)
				txtXPos = x - 3;
			else
				txtXPos = x - text->getText().length() / 2 + 6;

			item->setWorldPosition(x, y);
			text->setWorldPosition(txtXPos, item->getWorldPosition().Y + 5);

			obj_ptr.push_back(item);
			obj_ptr.push_back(text);

			shop_obj_ptr.push_back(item);
			shop_obj_ptr.push_back(text);
		}

		std::ifstream file("LEVELS\\" + levelName + ".txt");
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
				else if (line_array.at(0) == "BeeHive_Icon") {
					GameObject* ptr = new BeeHive(BEEHIVE_ICON);
					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
				}
				else if (line_array.at(0) == "FireStation") {
					GameObject* ptr = new FireStation();
					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
				}
				else if (line_array.at(0) == "Forest") {
					GameObject* ptr = new Forest();
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
				else if (line_array.at(0) == "MiniGame_WL") {
					MiniGame* ptr = new MiniGame_WL(level, console);
					levelStates.push_back(ptr->getAssociatedLSState());

					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
					mg_ptr.push_back(ptr);
				}
				else if (line_array.at(0) == "MiniGame_BHOS") {
					MiniGame* ptr = new MiniGame_BHOS(level, console);
					levelStates.push_back(ptr->getAssociatedLSState());

					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
					mg_ptr.push_back(ptr);
				}
				else if (line_array.at(0) == "MiniGame_RW") {
					MiniGame* ptr = new MiniGame_RW(level, console);
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
				else if (line_array.at(0) == "L_Road") {
					ROADTYPE type = R_L;
					GameObject* ptr = new Road(type);
					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
				}
				else if (line_array.at(0) == "Right_L_Road") {
					ROADTYPE type = R_RL;
					GameObject* ptr = new Road(type);
					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
				}
				else if (line_array.at(0) == "Left_Up_L_Road") {
					ROADTYPE type = R_LUL;
					GameObject* ptr = new Road(type);
					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
				}
				else if (line_array.at(0) == "Right_Up_L_Road") {
					ROADTYPE type = R_RUL;
					GameObject* ptr = new Road(type);
					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
				}
				else if (line_array.at(0) == "Down_T_Road") {
					ROADTYPE type = R_DT;
					GameObject* ptr = new Road(type);
					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
				}
				else if (line_array.at(0) == "Up_T_Road") {
					ROADTYPE type = R_UT;
					GameObject* ptr = new Road(type);
					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
				}
				else if (line_array.at(0) == "Left_Vertical_T_Road") {
					ROADTYPE type = R_LVT;
					GameObject* ptr = new Road(type);
					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
				}
				else if (line_array.at(0) == "Right_Vertical_T_Road") {
					ROADTYPE type = R_RVT;
					GameObject* ptr = new Road(type);
					ptr->setWorldPosition(std::stoi(line_array.at(1)), std::stoi(line_array.at(2)));
					obj_ptr.push_back(ptr);
				}
				else if (line_array.at(0) == "Cross_Road") {
					ROADTYPE type = R_X;
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
		case LS_MAINMENU: mapSize = { (213 + 67 * 3 + 20) ,50 }; break;
		case LS_BEGIN_SCENE: mapSize = { 213,50 }; break;

		case LS_LEVEL_BUILDER:
		case LS_MAINGAME:
			mapSize = mainMapSize;
			mapDisplayOffset = mainDisplayOrigin;
			break;
		case LS_GAMESHOP:
			mapSize = { 626,50 }; break;

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
		element = nullptr;
	}
	for (auto& entry : levelspecific_maps) {
		delete entry.second;
		entry.second = nullptr;
	}
	delete pickedUp_obj;
	currently_played_MG_ptr = NULL;
	pickedUp_obj = NULL;
	player_ptr = NULL;
	truck_ptr = NULL;
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
	switch (state) {
	case LS_GAMESHOP:
		for (auto& objs : obj_ptr) {
			objs->setActive(false);
		}
		for (auto& shop_objs : shop_obj_ptr) {
			shop_objs->setActive(true);
		}
		Money_ptr->setActive(true);
		break;
	case LS_MAINGAME:
		for (auto& objs : obj_ptr) {
			objs->setActive(true);
		}
		for (auto& shop_objs : shop_obj_ptr) {
			shop_objs->setActive(false);
		}
		player_ptr->setActive(false);
		break;
	}

	originalState = state;
}

LEVEL Level::getLevel() {
	return level;
}

LEVEL Level::getNextLevel() {
	return nextLevel;
}

void Level::resetNextLevel() {
	(*this).nextLevel = level;
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
		if (object_ptr->getType() != "Text")
			sort.insert(std::pair<short, GameObject*>(object_ptr->getWeight() * (-1), object_ptr));
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

void Level::updateProgressDisplays() {
	Money_ptr->setText(getMoneyBalancePrefix());

	ft_waterCollected->setProgress(truck_ptr->getCurrentWaterLevel()/truck_ptr->getMaxWater() * 100);
	ft_waterCollected_text->setText(getTruckWaterPrefix());

	level_progress->setProgress(fire / originalTotalFire * 100);
	level_progress_text->setText(getFireRemainingPrefix());
}

std::string Level::getTruckWaterPrefix() {
	return "Truck's Water (" + std::to_string((int)truck_ptr->getCurrentWaterLevel()) + "L/" + std::to_string((int)truck_ptr->getMaxWater())+"L)";
}

std::string Level::getFireRemainingPrefix() {
	return "Fire Remaining: " + std::to_string((int) fire);
}

std::string Level::getMoneyBalancePrefix() {
	return "Funds: $" + std::to_string(player_ptr->getMoney());
}

