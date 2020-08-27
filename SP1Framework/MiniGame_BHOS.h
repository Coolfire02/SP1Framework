#pragma once
#include "MiniGame.h"
#include "BeeHive.h"
class MiniGame_BHOS :
    public MiniGame
{
private:
    std::string amount;
    int ms;
    Text* Instructions;
    Text* Money_ptr;
    Text* hive_selected_text;
    BeeHive* selectedHive;
    std::vector<BeeHive*> mg_hive_ptr;
    std::vector<BeeHive*> mg_fallingHive_ptr;

    //for beehive grabbing
    COORD lastMousePos;
    COORD* grabbedHivePos;
    int beeHiveLeft;
    int beeHiveRight;

    //stats
    int msPassed;

    //player game stat
    int playerLives;
    int maxPlayerLives;

    //health bar
    ProgressBar* health_bar;

    COORD TreeMax, TreeMin;
    int numHive;
public:
    void setMoneyText();
    std::string getType();
    enum LEVELSTATE getAssociatedLSState();

    MiniGame_BHOS(LEVEL level, Console& console);
    ~MiniGame_BHOS();

    void mgGameInit();
    void gameLoopListener();
    bool processKBEvents_mg(SKeyEvent KeyEvents[]);
    bool processMouseEvents_mg(SMouseEvent&);

    MiniGame_BHOS* clone() const { return new MiniGame_BHOS(*this); };
};

