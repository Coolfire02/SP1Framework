#pragma once
#include <Windows.h>

extern CHAR_INFO g_background;
extern CHAR_INFO g_errorchar;
extern COORD g_consoleSize;

extern double  g_dElapsedTime;
extern double  g_dDeltaTime;

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
    K_SPACE,
    K_CTRL,
    K_W,
    K_A,
    K_S,
    K_D,
    K_C,
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
};

enum BAR {
    B_HORIZONTAL,
    B_VERTICAL
};