#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

extern CHAR_INFO g_background;
extern CHAR_INFO g_errorchar;
extern COORD g_consoleSize;

extern double  g_dElapsedTime;
extern double  g_dDeltaTime;

extern int g_loopInterval;

// struct to store keyboard events
// a small subset of KEY_EVENT_RECORD
struct SKeyEvent
{
    bool keyDown;
    bool keyReleased;
};

// struct to store mouse events
// a small subset of MOUSE_EVENT_RECORD
struct SMouseEvent
{
    COORD mousePosition;
    DWORD buttonState;
    DWORD eventFlags;
};

// Enumeration to store the control keys that your game will have
enum EKEYS
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_DELETE,
    K_SPACE,
    K_CTRL,
    K_W,
    K_V,
    K_A,
    K_S,
    K_D,
    K_C,
    K_R,
    K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_ACTIVE,
    S_HOLD,
    S_END,
    S_COUNT
};

//Enumeration for different levels
enum LEVEL {
    MAINMENU,
    TUTORIAL,
    STAGE_1_LEVEL_1,
    STAGE_2_LEVEL_1,
    LEVEL_COUNT
};

enum BAR {
    B_HORIZONTAL,
    B_VERTICAL
};

enum COINTYPE
{
    C_COIN,
    C_REDCOIN,
    C_BIGCOIN
};

enum HIVETYPE
{
    BEEHIVE,
    BEEHIVE_ICON
};

enum ITEMTYPE {
    ABILITY_ZOOM,
    ABILITY_ROADREPAIR,
    ABILITY_HOMEBASE,
    HOSE_HOLY_WATER,
    HOSE_MONEY_SALVAGER,
    HOSE_ABSORBER,
    HOSE_MAGICAL_WATER,
    HOSE_MONEY_DUPLICATOR,
    TOTAL_SHOP_ITEMS,


    UNLISTED_ITEM //This returns the total number of items in the shop too
};

enum WATERTYPE
{
    DROPLET,
    BOTTLE,
    HAIL
};

std::string round_2dp(double num);