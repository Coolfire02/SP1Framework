#pragma once
#include <Windows.h>
#include "MiniGame.h"
#include "Droplet.h"
#include "Jar.h"
#include <stdlib.h>
#include <time.h>  

class MiniGame_RW:
	public MiniGame
{
private:
    std::string amount;
    int ms;
    int droplet_spawn_delay;
    int droplet_fall_delay;
    std::vector<Droplet*> droplet_ptrs;
    Jar* jar_ptr;
    Text* Water_ptr;
    void addWater(COORD);
public:
    void setWaterText();
    std::string getType();
    enum LEVELSTATE getAssociatedLSState();

    MiniGame_RW(LEVEL level, Console& console);
    ~MiniGame_RW();

    void mgGameInit();
    void gameLoopListener();
    bool processKBEvents(SKeyEvent KeyEvents[]);
    bool processMouseEvents(SMouseEvent&);

    MiniGame_RW* clone() const { return new MiniGame_RW(*this); };
};
