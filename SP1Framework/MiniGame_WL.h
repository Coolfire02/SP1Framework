#pragma once
#include "MiniGame.h"
#include <Windows.h>
#include "MiniGame.h"
#include <stdlib.h>
#include <time.h>  
#include "Bucket.h"
#include "Wrench.h"
#include "Pipe.h"

class MiniGame_WL : 
    public MiniGame
{
private:
    int ms;
    int UPcount = 0;
    int DOWNcount = 0;
    int water_spawn_delay;
    Bucket* bucket_ptr;
    Text* water_ptr;
    Wrench* wrench_ptr;
    Wrench* wrench_ptr2;
    Pipe* pipe_ptr;
public:
    void setWaterText();
    std::string getType();
    enum LEVELSTATE getAssociatedLSState();

    MiniGame_WL(LEVEL level, Console& console);
    ~MiniGame_WL();

    void mgGameInit();
    void gameLoopListener();
    bool processKBEvents(SKeyEvent KeyEvents[]);
    bool processMouseEvents(SMouseEvent&);

};

