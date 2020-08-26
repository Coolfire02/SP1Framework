#pragma once
#include "MiniGame.h"
class MiniGame_CFT :
    public MiniGame
{

public:

	MiniGame_CFT(LEVEL level, Console& console);
	~MiniGame_CFT();

	void mgGameInit();
	void gameLoopListener();
	bool processKBEvents(SKeyEvent[]);
	bool processMouseEvents(SMouseEvent&);
	enum LEVELSTATE getAssociatedLSState();
	std::string getType();

	MiniGame_CFT* clone() const { return new MiniGame_CFT(*this); };
};

