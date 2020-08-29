#pragma once

#include "CutScene.h"

class StartScene :
    public CutScene
{
private:
    int fall_delay;
    ArtObject* fireman_ptr;
    ArtObject* pole_ptr;

public:
    void cutsceneInit();
    StartScene(Console& console);
    std::string getType();
    ~StartScene();
    void CutSceneLoopListener();
};

