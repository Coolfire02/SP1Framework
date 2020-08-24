#pragma once
#include "MiniGame.h"
#include <Windows.h>
#include "MiniGame.h"
#include <stdlib.h>
#include <time.h>  
#include "Bucket.h"

class MiniGame_WL : 
    public MiniGame
{
private:
    int ms;
    int water_spawn_delay;
    Bucket* bucket_ptr;
    Text* Water_ptr;
    void addWater(COORD);
public:
    void setWaterText();
    std::string getType();
    enum LEVELSTATE getAssociatedLSState();

    MiniGame_WL(LEVEL level, Console& console);
    ~MiniGame_WL();

    void mgGameInit();
    void gameLoopListener();
    bool processKBEvents(SKeyEvent[]);
    bool processMouseEvents(SMouseEvent&);

};

