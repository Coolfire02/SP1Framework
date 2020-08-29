#include "MiniGame_CFT.h"

MiniGame_CFT::MiniGame_CFT(LEVEL level, Console& console) : MiniGame(level, console)
{
	art.setArt(MINIGAME_CFT_ART);

}

MiniGame_CFT::~MiniGame_CFT()
{
	//Intentionally left blank
}

void MiniGame_CFT::mgGameInit()
{
	//Game Initialization
	srand(time(NULL));
	MiniGameMap.setSize(639,200);
	MiniGameMap.setBackground(0xB0);
	MiniGameMap.setMapToBufferOffset(COORD{ 213, 150 });

	player_ptr = new Player;
	tree = new ArtObject(20, 200, 0x0F, 0x0F, 1, "Tree");
	cat = new Cat();
	upcomingSteps = new Text("Up Coming Steps\n\n/////\n/////\n/////\n/////", 0x30);

	currentStep = -1;

	tree->setWorldPosition(309, 0);
	COORD playerPos;
	playerPos.X = (MiniGameMap.getXLength() / 2 - (player_ptr->getXLength() / 2));
	playerPos.Y = (MiniGameMap.getYLength() - player_ptr->getYLength() - 1);
	upcomingSteps->setRelativePos(160, 40);

	player_ptr->setWorldPosition(playerPos);

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

	updateSteps();

	//Branches generation
	//left side
	for (short y = MiniGameMap.getYLength(); y > MiniGameMap.getYLength() - pathHeight + 6; y--) {
		if (rand() % 12 == 0) {
			int branchSize = rand() % 45 + 18;
			ArtObject* branch = new ArtObject(branchSize - 1, 1, 0x0F, 0x0F, 1, "Branch");
			branch->setWorldPosition(pathXMax+1, y);
			mg_obj_ptr.push_back(branch);
		}
	}
	//right side
	for (short y = MiniGameMap.getYLength(); y > MiniGameMap.getYLength() - pathHeight + 6; y--) {
		if (rand() % 13 == 0) {
			int branchSize = rand() % 45 + 18;
			ArtObject* branch = new ArtObject(branchSize - 1, 1, 0x0F, 0x0F, 1, "Branch");
			branch->setWorldPosition(pathXMin - branchSize + 1, y);
			mg_obj_ptr.push_back(branch);
		}
	}

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
	Text* Line3 = new Text("Cat Alertness: Low", MiniGameMap.getBackground());
	Line3->setRelativePos(g_consoleSize.X / 2 - Line3->getText().length() / 2, 10);
	instructions_obj_ptr.push_back(Line3);
	Text* Line4 = new Text("Reward: $300", MiniGameMap.getBackground());
	Line4->setRelativePos(g_consoleSize.X / 2 - Line4->getText().length() / 2, 11);
	instructions_obj_ptr.push_back(Line4);

	button_ptr = new Text("Start Game", 0x70);
	button_ptr->setRelativePos(g_consoleSize.X / 2 - button_ptr->getText().length() / 2, 16);
	instructions_obj_ptr.push_back(button_ptr);
}

void MiniGame_CFT::gameLoopListener()
{
	if (isStarted() && !isInInstructions)
	{
		
	}
}

bool MiniGame_CFT::processKBEvents_mg(SKeyEvent keyEvents[])
{
	bool eventIsProcessed = false;
	COORD player_orig_pos = player_ptr->getWorldPosition();

	if (currentStep + 1 >= path.size()) return false;

	EKEYS nextStepKey = path.at(currentStep+1);
	if (keyEvents[K_W].keyDown) {
		if (nextStepKey == K_W) {
			player_ptr->setWorldPosition(player_orig_pos.X, player_orig_pos.Y - 1);
			currentStep += 1;
		}
		else {
			//add to cat meter and saying you missed the step by pressing the wrong key, you have alerted the cat
		}
		eventIsProcessed = true;
	}
	if (keyEvents[K_A].keyDown)
	{
		if (nextStepKey == K_A) {
			player_ptr->setWorldPosition(player_orig_pos.X-1, player_orig_pos.Y);
			currentStep += 1;
		}
		else {
			//add to cat meter and saying you missed the step by pressing the wrong key, you have alerted the cat
		}
		eventIsProcessed = true;
	}
	if (keyEvents[K_D].keyDown)
	{
		if (nextStepKey == K_D) {
			player_ptr->setWorldPosition(player_orig_pos.X+1, player_orig_pos.Y);
			currentStep += 1;
		}
		else {
			//add to cat meter and saying you missed the step by pressing the wrong key, you have alerted the cat
		}
		eventIsProcessed = true;
	}
	if (eventIsProcessed)
		updateSteps();
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
	for (int i = 1; i <= 4; i++) {
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