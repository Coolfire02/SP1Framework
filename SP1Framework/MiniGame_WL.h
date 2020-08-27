#pragma once
#include "MiniGame.h"
#include <Windows.h>
#include "MiniGame.h"
#include <stdlib.h>
#include <time.h>  
#include <iostream>
#include "Bucket.h"
#include "Wrench.h"
#include "Pipe.h"

class MiniGame_WL : 
    public MiniGame
{
private:
    int UPcount;
    int DOWNcount;
    bool isDown;
    int ms;
    int water_leak;
    int water_spawn_delay;
    int water_amt_reduction;
    int water_wasted, payreduction;
    Bucket* bucket_ptr;
    ProgressBar* water_ptr;
    Text* Money_ptr;
    Wrench* wrench_ptr;
    Wrench* wrench_ptr2;
    Pipe* pipe_ptr;
public:
    std::string getType();
    enum LEVELSTATE getAssociatedLSState();
    void setMoneyText();

    MiniGame_WL(LEVEL level, Console& console);
    ~MiniGame_WL();

    void mgGameInit();
    void gameLoopListener();
    bool processKBEvents_mg(SKeyEvent KeyEvents[]);
    bool processMouseEvents_mg(SMouseEvent&);

    MiniGame_WL* clone() const { return new MiniGame_WL(*this); };
};

