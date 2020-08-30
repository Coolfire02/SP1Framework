// This is the main file for the game logic and function
//
//
#include "global.h"
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>

#include "GameObject.h"
#include "FireTruck.h"
#include "Player.h"

#include "MiniGame.h"
#include "MiniGame_RM.h"

double  g_keyCooldownTime;
double  g_mouseCooldownTime;
bool loaded = false;
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;

// Game specific variables here

EGAMESTATES g_eGameState = S_ACTIVE; // initial state

// Console object
Console g_Console(g_consoleSize, "SP1 Framework");
Level* levels[4];

//Loading of levels before main()
int load_levels() {
    g_Console.writeToBuffer(g_consoleSize.X / 2 - 10, g_consoleSize.Y / 2, "Loading... 0%", 0xF0);
    levels[0] = new Level(MAINMENU, g_Console);
    g_Console.writeToBuffer(g_consoleSize.X / 2 - 10, g_consoleSize.Y / 2, "Loading... 25%", 0xF0);
    levels[1] = new Level(TUTORIAL, g_Console);
    g_Console.writeToBuffer(g_consoleSize.X / 2 - 10, g_consoleSize.Y / 2, "Loading... 50%", 0xF0);
    levels[2] = new Level(STAGE_1_LEVEL_1, g_Console);
    g_Console.writeToBuffer(g_consoleSize.X / 2 - 10, g_consoleSize.Y / 2, "Loading... 75%", 0xF0);
    levels[3] = new Level(STAGE_2_LEVEL_1, g_Console); 
    g_Console.writeToBuffer(g_consoleSize.X / 2 - 10, g_consoleSize.Y / 2, "Loading... 100%", 0xF0);
    return 0;
}

Level* g_Level;

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;    

    // sets the initial state for the game
    g_eGameState = S_ACTIVE;
    
    //level declaration (use ptrs)
    g_Level = levels[MAINMENU];

    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    g_Console.clearBuffer();
    delete g_Level;
}

//--------------------------------------------------------------
// Purpose  : Get all the console input events
//            This function sets up the keyboard and mouse input from the console.
//            We will need to reset all the keyboard status, because no events will be sent if no keys are pressed.
//
//            Remember to set the handlers for keyboard and mouse events.
//            The function prototype of the handler is a function that takes in a const reference to the event struct
//            and returns nothing. 
//            void pfKeyboardHandler(const KEY_EVENT_RECORD&);
//            void pfMouseHandlerconst MOUSE_EVENT_RECORD&);
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{
    // resets all the keyboard events
    memset(g_skKeyEvent, 0, K_COUNT * sizeof(*g_skKeyEvent));
    // then call the console to detect input from user
    g_Console.readConsoleInput();    
}

void startNextLevel(LEVEL level) {
    g_Level->resetNextLevel();

    if (levels[level]->isComplete() == false) {
        g_Level = levels[level];
        g_Level->StartLevel();
    }
    else {
        if (g_Level->getLevel() == MAINMENU) {
            g_Level->setTopOfScreenTXT("Level already completed!");
        }
    }
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the keyboard input. Whenever there is a keyboard event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            The KEY_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any keyboard event in the Splashscreen state
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent - reference to a key event struct
// Output   : void
//--------------------------------------------------------------
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent)
{    
    switch (g_eGameState)
    {
    case S_ACTIVE: gameplayKBHandler(keyboardEvent);
        break;
    case S_HOLD:
        break;
    case S_END:
        break;
    }
}

void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{    
    switch (g_eGameState)
    {
    case S_ACTIVE: 
    case S_HOLD:
        gameplayMouseHandler(mouseEvent);
        break;
    case S_END:
        break;
    }
}

void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent)
{
    // here, we map the key to our enums
    EKEYS key = K_COUNT;
    switch (keyboardEvent.wVirtualKeyCode)
    {
    case VK_UP: key = K_UP; break;
    case VK_DOWN: key = K_DOWN; break;
    case VK_LEFT: key = K_LEFT; break; 
    case VK_RIGHT: key = K_RIGHT; break; 
    case VK_SPACE: key = K_SPACE; break;
    case VK_DELETE: key = K_DELETE; break;
    case VK_ESCAPE: key = K_ESCAPE; break; 
    case VK_CONTROL: key = K_CTRL; break;
    case 0x43: key = K_C; break;
    case 0x52: key = K_R; break;
    case 0x56: key = K_V; break;
    case 0x57: key = K_W; break;
    case 0X41: key = K_A; break;
    case 0x53: key = K_S; break;
    case 0x44: key = K_D; break;
    }
    if (key != K_COUNT)
    {
        g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;
        g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;
        bool ctrlPressed = keyboardEvent.dwControlKeyState & (RIGHT_CTRL_PRESSED | LEFT_CTRL_PRESSED);
        g_skKeyEvent[K_CTRL].keyDown = ctrlPressed;
        g_skKeyEvent[K_CTRL].keyReleased = !ctrlPressed;
        
    }    
}

void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{
    if (mouseEvent.dwEventFlags & MOUSE_MOVED) // update the mouse position if there are no events
    {
        g_mouseEvent.mousePosition = mouseEvent.dwMousePosition;
    }
    g_mouseEvent.buttonState = mouseEvent.dwButtonState;
    g_mouseEvent.eventFlags = mouseEvent.dwEventFlags;
}

void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;
    switch (g_eGameState)
    {
        case S_ACTIVE : updateGame();
            break;
        case S_HOLD: updateOptions();
            break;
    }
}

void processUserInput()
{
    // Manages quitting using escape
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
        if (g_Level->getLevel() == MAINMENU)
            g_bQuitGame = true;
        else if (g_Level->getState() == LS_GAMESHOP) {
            g_Level->setState(LS_MAINGAME);
        }
        else
            startNextLevel(MAINMENU);
}

void updateOptions()
{
    processUserInput();
    optionMenuClick();
}

void updateGame()       // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    updateLevel();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void optionMenuClick() // handling of clicks in options menu
{

}

void updateLevel() {
    g_Level->gameLoopListener(); //A while loop listened every 20ms.
    // processing key/mouse inputs for levels
    if (g_keyCooldownTime < g_dElapsedTime) {
        if (g_Level->processKBEvents(g_skKeyEvent)) { //successfully processed?
            g_keyCooldownTime = g_dElapsedTime + 0.05; //add cooldown
        }
    }
    if (g_mouseCooldownTime < g_dElapsedTime) {
        if (g_Level->processMouseEvents(g_mouseEvent)) { //successfully processed?
            g_mouseCooldownTime = g_dElapsedTime + 1; //add cooldown
        }
    }
}


void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
    case S_ACTIVE: renderLevel();
        break;
    case S_HOLD: renderOptions();
        break;
    }
    renderFramerate();      // renders debug information, frame rate, elapsed time, etc
    //renderInputEvents();    // renders status of input events
    renderToScreen();       // dump the contents of the buffer to the screen, one frame worth of game
}

void clearScreen()
{
    g_Console.clearBuffer(0x80);
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void renderLevel() {
    
    g_Level->checkStateChange();
    g_Level->renderObjsToMap();
    g_Level->renderMap();
}

void renderOptions() {

}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());
}
int once = false;

void updateGameState() {
    if (g_Level->getLevel() != g_Level->getNextLevel()) {
        startNextLevel(g_Level->getNextLevel());
        return;
    }
}