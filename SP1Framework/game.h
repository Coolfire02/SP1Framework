#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "Level.h"

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

int load_levels  ( void );
void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void updateGameState(void);		// helps change the game after all renders and inputs have been processed
void shutdown    ( void );      // do clean up, free memory

//void splashScreenWait();    // waits for time to pass in splash screen
void updateGame();          // gameplay logic
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void updateOptions();
void updateLevel();
void optionMenuClick();
void renderLevel();
void renderOptions();

// keyboard and mouse input event managers
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent);  // define this function for the console to call when there are keyboard events
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent);      // define this function for the console to call when there are mouse events

void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent);   // handles keyboard events for gameplay 
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent); // handles mouse events for gameplay 


#endif // _GAME_H