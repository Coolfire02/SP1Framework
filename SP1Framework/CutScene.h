#pragma once

#include "Framework/console.h"
#include "ArtObject.h"
#include "Map.h"

#include <vector>
#include <string>
#include <map>
#include <list>
#include <time.h>

class CutScene
{
private:
	double CS_start_time;
	bool CS_started;
	virtual void cutsceneInit() = 0; // when start() is called, it'll call this for all cutscenes to read

protected:
	int ms;
	Console associatedConsole;
	bool Completed;
	std::vector<ArtObject*> CS_obj_ptr;
	Map Scene;


public:
	CutScene(Console& console);
	~CutScene();

	void start();
	void renderMap();
	void renderObjsToMap();
	COORD getMapSize();

	bool isCompleted();
	bool isStarted();

	double getStartTime();

	virtual std::string getType() = 0;

	virtual void CutSceneLoopListener() = 0;
};

