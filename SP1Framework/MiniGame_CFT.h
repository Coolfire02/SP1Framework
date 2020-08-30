#pragma once
#include "MiniGame.h"
#include "ArtObject.h"
#include "Cat.h"
#include "Text.h"
#include <vector>

class MiniGame_CFT :
    public MiniGame
{
private:
	ArtObject* tree;
	Cat* cat;
	Text* upcomingSteps;
	ProgressBar* catAlertnessBar;
	Text* topOfScreenTXT;

	unsigned int currentStep;
	int earnValue;
	double timeOfPreviousStep;

	std::vector<EKEYS> path;
	short pathHeight;
	short pathXMin;
	short pathXMax;

	double catAlertnessThreshold;
	double catAlertness;
	
	std::string pathToString(EKEYS key);
	void updateSteps();
	void setTopText(std::string);
	void updateCatAlertnessBar();
public:
	MiniGame_CFT(LEVEL level, Console& console);
	~MiniGame_CFT();

	void mgGameInit();
	void gameLoopListener();
	bool processKBEvents_mg(SKeyEvent[]);
	bool processMouseEvents_mg(SMouseEvent&);
	enum LEVELSTATE getAssociatedLSState();
	std::string getType();

	MiniGame_CFT* clone() const { return new MiniGame_CFT(*this); };
};

