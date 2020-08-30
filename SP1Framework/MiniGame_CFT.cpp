#include "MiniGame_CFT.h"

MiniGame_CFT::MiniGame_CFT(LEVEL level, Console& console) : MiniGame(level, console)
{
	pathXMin = 0;
	pathXMax = 0;
	pathHeight = 0;
	currentStep = 0;
	upcomingSteps = NULL;
	tree = NULL;
	topOfScreenTXT = NULL;
	catAlertnessBar = NULL;
	cat = NULL;
	timeOfPreviousStep = NULL;
	art.setArt(MINIGAME_CFT_ART);
	earnValue = 75 + 25 * level;
	catAlertnessThreshold = 100 - 7 * pow(level,0.5);
	catAlertness = 0;
}

MiniGame_CFT::~MiniGame_CFT()
{
	//Intentionally left blank
}

void MiniGame_CFT::mgGameInit()
{
	//Game Initialization
	srand((unsigned int)(time(NULL)));
	MiniGameMap.setSize(639,200);
	MiniGameMap.setBackground(0xB0);
	MiniGameMap.setMapToBufferOffset(COORD{ 213, 150 });

	player_ptr = new Player;
	tree = new ArtObject(20, 200, 0x0F, 0x0F, 1, "Tree");
	cat = new Cat();
	upcomingSteps = new Text("Up Coming Steps\n\n/////\n/////\n/////\n/////", 0x30);
	catAlertnessBar = new ProgressBar(B_VERTICAL, 5, 10, 0x20, 0xC0);
	topOfScreenTXT = new Text("/", 0x2F);

	currentStep = -1;

	tree->setWorldPosition(309, 0);
	COORD playerPos;
	playerPos.X = (MiniGameMap.getXLength() / 2 - (player_ptr->getXLength() / 2));
	playerPos.Y = (MiniGameMap.getYLength() - player_ptr->getYLength() - 1);
	upcomingSteps->setRelativePos(160, 40);
	topOfScreenTXT->setRelativePos(g_consoleSize.X / 2 - topOfScreenTXT->getText().length() / 2, 0);
	player_ptr->setWorldPosition(playerPos);
	catAlertnessBar->setRelativePos(160, 20);
	catAlertnessBar->setProgress(0);

	mg_obj_ptr.push_back(topOfScreenTXT);
	mg_obj_ptr.push_back(catAlertnessBar);
	mg_obj_ptr.push_back(upcomingSteps);
	mg_obj_ptr.push_back(player_ptr);
	mg_obj_ptr.push_back(tree);
	mg_obj_ptr.push_back(cat);

	pathHeight = 20 + 4 * getAssociatedLevel();
	pathXMin = 309;
	pathXMax = 325;

	COORD generated_path = player_ptr->getWorldPosition();
	
	//Path generation
	int keyGenerationY = 0;
	while (keyGenerationY < pathHeight) {
		int ran = rand() % 20;
		if (ran <= 5) {
			if (ran % 2 == 0) {
				if (generated_path.X > pathXMin)
					path.push_back(K_A);
				else
					path.push_back(K_D);
			}
			else {
				if (generated_path.X < pathXMax)
					path.push_back(K_D);
				else
					path.push_back(K_A);
			}
		}
		else {
			path.push_back(K_W);
			keyGenerationY++;
		}
	}

	//Branches generation
	//left side
	for (unsigned short y = MiniGameMap.getYLength(); y > MiniGameMap.getYLength() - pathHeight + 7; y--) {
		if (rand() % 12 == 0) {
			int branchSize = rand() % 45 + 18;
			ArtObject* branch = new ArtObject(branchSize - 1, 1, 0x0F, 0x0F, 1, "Branch");
			branch->setWorldPosition(pathXMax+1, y);
			mg_obj_ptr.push_back(branch);
		}
	}

	ArtObject* catBranch = new ArtObject(30, 1, 0x0F, 0x0F, 1, "Cat_Branch");
	catBranch->setWorldPosition(pathXMax + 1, MiniGameMap.getYLength() - pathHeight + 3 - player_ptr->getYLength());
	mg_obj_ptr.push_back(catBranch);
	cat->setWorldPosition(pathXMax + 4, catBranch->getWorldPosition().Y-4);

	for(signed int i = 0; i < ((pathXMax)-generated_path.X+12); i++)
		path.push_back(K_D);

	//right side
	for (unsigned short y = MiniGameMap.getYLength(); y > MiniGameMap.getYLength() - pathHeight + 7; y--) {
		if (rand() % 13 == 0) {
			int branchSize = rand() % 45 + 18;
			ArtObject* branch = new ArtObject(branchSize - 1, 1, 0x0F, 0x0F, 1, "Branch");
			branch->setWorldPosition(pathXMin - branchSize + 1, y);
			mg_obj_ptr.push_back(branch);
		}
	}

	updateSteps();

	//Instructions for Raining Money Game
	Text* Title = new Text("Save the Cat!", MiniGameMap.getBackground());
	Title->setRelativePos(g_consoleSize.X / 2 - Title->getText().length() / 2, 5);
	instructions_obj_ptr.push_back(Title);
	Text* Line1 = new Text("Manuever up the tree without alerting the cat.", MiniGameMap.getBackground());
	Line1->setRelativePos(g_consoleSize.X / 2 - Line1->getText().length() / 2, 8);
	instructions_obj_ptr.push_back(Line1);
	Text* Line2 = new Text("Use W A S D to climb up the Tree. Good luck!", MiniGameMap.getBackground());
	Line2->setRelativePos(g_consoleSize.X / 2 - Line2->getText().length() / 2, 9);
	instructions_obj_ptr.push_back(Line2);
	std::string tier = "Low";
	if (catAlertnessThreshold > 33.33 && catAlertnessThreshold <= 66.66) tier = "Normal";
	else if (catAlertnessThreshold <= 33.33) tier = "High";
	Text* Line3 = new Text("Cat Alertness: Low", MiniGameMap.getBackground());
	Line3->setRelativePos(g_consoleSize.X / 2 - Line3->getText().length() / 2, 10);
	instructions_obj_ptr.push_back(Line3);
	Text* Line4 = new Text("Reward: $"+std::to_string(earnValue), MiniGameMap.getBackground());
	Line4->setRelativePos(g_consoleSize.X / 2 - Line4->getText().length() / 2, 11);
	instructions_obj_ptr.push_back(Line4);

	button_ptr = new Text("Start Game", 0x70);
	button_ptr->setRelativePos(g_consoleSize.X / 2 - button_ptr->getText().length() / 2, 16);
	instructions_obj_ptr.push_back(button_ptr);

	timeOfPreviousStep = g_dElapsedTime;
}

void MiniGame_CFT::gameLoopListener()
{
	if (isStarted() && !isInInstructions)
	{
		if (catAlertness >= catAlertnessThreshold) {
			Completed = true;
		}
		else {
			if (currentStep != -1) {
				if (g_dElapsedTime-timeOfPreviousStep > 1) {
					setTopText("Taking too long! You are alerting the cat!");
					catAlertness += 1.5 + 0.2 * getAssociatedLevel();
					updateCatAlertnessBar();
					timeOfPreviousStep = g_dElapsedTime;
				}
			}
		}
	}
}

bool MiniGame_CFT::processKBEvents_mg(SKeyEvent keyEvents[])
{
	bool eventIsProcessed = false;
	COORD player_orig_pos = player_ptr->getWorldPosition();

	if (currentStep + 1 >= path.size()) return false;

	EKEYS nextStepKey = path.at(currentStep+1);
	if (keyEvents[K_W].keyReleased) {
		if (nextStepKey == K_W) {
			player_ptr->setWorldPosition(player_orig_pos.X, player_orig_pos.Y - 1);
			currentStep += 1;
			timeOfPreviousStep = g_dElapsedTime;
		}
		else {
			setTopText("Wrong Step! You are alerting the cat!");
			catAlertness += 1;
			updateCatAlertnessBar();
		}
		eventIsProcessed = true;
	}
	if (keyEvents[K_A].keyReleased)
	{
		if (nextStepKey == K_A) {
			player_ptr->setWorldPosition(player_orig_pos.X-1, player_orig_pos.Y);
			currentStep += 1;
			timeOfPreviousStep = g_dElapsedTime;
		}
		else {
			setTopText("Wrong Step! You are alerting the cat!");
			catAlertness += 1;
			updateCatAlertnessBar();
		}
		eventIsProcessed = true;
	}
	if (keyEvents[K_D].keyReleased)
	{
		if (nextStepKey == K_D) {
			player_ptr->setWorldPosition(player_orig_pos.X+1, player_orig_pos.Y);
			currentStep += 1;
			timeOfPreviousStep = g_dElapsedTime;
		}
		else {
			setTopText("Wrong Step! You are alerting the cat!");
			catAlertness += 1;
			updateCatAlertnessBar();
		}
		eventIsProcessed = true;
	}
	if (eventIsProcessed) {
		timeOfPreviousStep = g_dElapsedTime;
		if (player_ptr->isCollided(*cat)) {
			MoneyEarned += earnValue;
			Completed = true;
		}
		updateSteps();
	}
	return eventIsProcessed;
}

bool MiniGame_CFT::processMouseEvents_mg(SMouseEvent&)
{
	return false;
}

std::string MiniGame_CFT::pathToString(EKEYS key) {
	switch (key) {
	case K_W:
		return "W";
	case K_A:
		return "A";
	case K_D:
		return "D";
	default:
		return "/";
	}
	return "/";
}

void MiniGame_CFT::updateSteps() {
	std::string upcomingStepStr = "Up Coming Steps\n\n";
	for (unsigned int i = 1; i <= 4; i++) {
		if (i == 1) upcomingStepStr.append(">> ");
		if (currentStep + i < path.size()) {
			for (int j = 0; j < 8; j++) {
				upcomingStepStr.append(pathToString(path.at(currentStep + i)));
			}
		}
		else {
			for (int j = 0; j < 8; j++)
				upcomingStepStr.append("/");
		}
		if (i == 1) upcomingStepStr.append(" <<");
		if (i < 4) upcomingStepStr.append("\n");
		
	}
	upcomingSteps->setText(upcomingStepStr);
}

LEVELSTATE MiniGame_CFT::getAssociatedLSState()
{
	return LS_MINIGAME_CFT;
}

std::string MiniGame_CFT::getType()
{
	return "MiniGame_CFT";
}

void MiniGame_CFT::setTopText(std::string text) {
	if (topOfScreenTXT != NULL) {
		topOfScreenTXT->setText(text);
		topOfScreenTXT->setRelativePos(g_consoleSize.X / 2 - topOfScreenTXT->getText().length() / 2, 0);
	}
}

void MiniGame_CFT::updateCatAlertnessBar() {
	if (catAlertnessBar != NULL) {
		catAlertnessBar->setProgress(catAlertness / catAlertnessThreshold * 100);
	}
}