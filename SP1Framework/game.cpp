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
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;

// Game specific variables here

EGAMESTATES g_eGameState = S_ACTIVE; // initial state

// Console object
Console g_Console(g_consoleSize, "SP1 Framework");
Level* g_Level = new Level(MAINMENU, g_Console); //initial state

void updateOptions();
void updateLevel();
void optionMenuClick();
void renderLevel();
void renderOptions();

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
    //UNDONE

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
    delete g_Level;
    g_Level = nullptr;
    g_Level = new Level(TUTORIAL, g_Console);
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
    case VK_ESCAPE: key = K_ESCAPE; break; 
    case VK_LCONTROL: key = K_CTRL; break;
    case 0x57: key = K_W; break;
    case 0X41: key = K_A; break;
    case 0x53: key = K_S; break;
    case 0x44: key = K_D; break;
    }
    if (key != K_COUNT)
    {
        g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;
        g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;
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

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
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
    // quits the game if player hits the escape key
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
        g_bQuitGame = true;
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
            g_keyCooldownTime = g_dElapsedTime + 0.09; //add cooldown
        }
    }
    g_Level->processMouseEvents(g_mouseEvent);
}

//void moveCharacter()
//{    
//    if (g_keyCooldownTime < g_dElapsedTime) {
//        // Updating the location of the character based on the key release
//        // providing a beep sound whenver we shift the character
//        bool movementUpdate = false;
//
//        if (g_skKeyEvent[K_W].keyDown && g_sChar.m_cLocation.Y > 0)
//        {
//            //Beep(1440, 30);
//            g_sChar.m_cLocation.Y--;
//            movementUpdate = true;
//        }
//        if (g_skKeyEvent[K_A].keyDown && g_sChar.m_cLocation.X > 0)
//        {
//            //Beep(1440, 30);
//            g_sChar.m_cLocation.X--;
//            movementUpdate = true;
//        }
//        if (g_skKeyEvent[K_S].keyDown && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
//        {
//            //Beep(1440, 30);
//            g_sChar.m_cLocation.Y++;
//            movementUpdate = true;
//        }
//        if (g_skKeyEvent[K_D].keyDown && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
//        {
//            //Beep(1440, 30);
//            g_sChar.m_cLocation.X++;
//            movementUpdate = true;
//        }
//        if (g_skKeyEvent[K_SPACE].keyDown)
//        {
//            g_sChar.m_bActive = !g_sChar.m_bActive;
//            movementUpdate = true;
//        }
//        if (movementUpdate) {
//            g_keyCooldownTime = g_dElapsedTime + 0.09;
//        }
//
//    }
//}

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
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
    
    //g_Level.checkStateChange();
    g_Level->renderObjsToMap();
    g_Level->renderMap();
}

void renderOptions() {

}

//Unused code but can use for ref. for positioning
//void renderSplashScreen()  // renders the splash screen
//{
//    COORD c = g_Console.getConsoleSize();
//    c.Y /= 3;
//    c.X = c.X / 2 - 9;
//    g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
//    c.Y += 1;
//    c.X = g_Console.getConsoleSize().X / 2 - 20;
//    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
//    c.Y += 1;
//    c.X = g_Console.getConsoleSize().X / 2 - 9;
//    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
//}

//Unused code but can be used for ref. later on
//void renderGame()
//{
//    renderMap();        // renders the map to the buffer first
//    renderCharacter();  // renders the character into the buffer
//}

//void renderMap()
//{
//    WORD mycolour = (short) 0xFFFFFF; 
//    // Set up sample colours, and output shadings
//    const WORD colors[] = {
//        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
//        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
//    };
//
//    COORD c;
//    for (int i = 0; i < 12; ++i)
//    {
//        c.X = 5 * i;
//        c.Y = i + 1;
//        
//        //g_Console.writeToBuffer(c, " °±²Û", colors[i]);
//        std::string s = "0x1F";
//        unsigned int thecolor = std::stoul(s, nullptr, 16);
//        WORD theAttri = thecolor;
//        //colour(0xF0);
//        WORD test = 0x1A;
//        g_Console.writeToBuffer(c, 'T', thecolor);
//        
//    }
//}

//void renderCharacter()
//{
//    // Draw the location of the character
//    WORD charColor = 0x0C;
//    if (g_sChar.m_bActive)
//    {
//        charColor = 0x0A;
//    }
//    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
//    player->setWorldPosition(4, 4);
//    for (int i = 0; i < player->getXLength(); i++) {
//        for (int j = 0; j < player->getYLength(); j++) {
//            g_Console.writeToBuffer(10, 10, ("getting" + i + ' ' + j));
//            COORD c = {i,j};
//            CHAR_INFO art = player->getArtAtLoc(c);
//            c.X += player->getWorldPosition().X;
//            c.Y += player->getWorldPosition().Y;
//            g_Console.writeToBuffer(c, art.Char.AsciiChar, art.Attributes);
//        }
//    }
//
//    if (ft->isCollided((*player))) {
//        g_Console.writeToBuffer(10, 10, "ISCOLLIDED YAY");
//    }
//    else {
//        g_Console.writeToBuffer(10, 10, "IS NOT COLLIDED BOO");
//    }
//}

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

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}
int once = false;

void updateGameState() {
    /*if (g_Level->getLevel() != g_Level->getNextLevel()) {
        startNextLevel(g_Level->getNextLevel());
        return;
    }*/
    /*delete g_Level;
    g_Level = nullptr;
    g_Level = new Level(TUTORIAL, g_Console);*/
    if (g_dElapsedTime > 3.0 && !once) {
        once = true;
        Beep(5000, 50);
        //startNextLevel(TUTORIAL);
        delete g_Level;
        g_Level = nullptr;
        g_Level = new Level(TUTORIAL, g_Console);
    }
}

// this is an example of how you would use the input events
//void renderInputEvents()
//{
//    // keyboard events
//    //COORD startPos = {50, 2};
//    //std::ostringstream ss;
//    std::string key;
//    for (int i = 0; i < K_COUNT; ++i)
//    {
//        switch (i)
//        {
//        case K_W: key = "UP";
//            break;
//        case K_S: key = "DOWN";
//            break;
//        case K_A: key = "LEFT";
//            break;
//        case K_D: key = "RIGHT";
//            break;
//        case K_SPACE: key = "SPACE";
//            break;
//        default: continue;
//        }
//        //if (g_skKeyEvent[i].keyDown)
//        //    ss << key << " pressed";
//        //else if (g_skKeyEvent[i].keyReleased)
//        //    ss << key << " released";
//        //else
//        //    ss << key << " not pressed";
//
//        //COORD c = { startPos.X, (short) (startPos.Y + i) };
//        //g_Console.writeToBuffer(c, ss.str(), 0x17);
//    }
//
//    // mouse events    
//    //ss.str("");
//    //ss << "Mouse position (" << g_mouseEvent.mousePosition.X << ", " << g_mouseEvent.mousePosition.Y << ")";
//    //g_Console.writeToBuffer(g_mouseEvent.mousePosition, ss.str(), 0x59);
//    //ss.str("");
//    switch (g_mouseEvent.eventFlags)
//    {
//    case 0:
//        if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
//        {
//            ss.str("Left Button Pressed");
//            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 1, ss.str(), 0x59);
//        }
//        else if (g_mouseEvent.buttonState == RIGHTMOST_BUTTON_PRESSED)
//        {
//            ss.str("Right Button Pressed");
//            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 2, ss.str(), 0x59);
//        }
//        else
//        {
//            ss.str("Some Button Pressed");
//            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 3, ss.str(), 0x59);
//        }
//        break;
//    case DOUBLE_CLICK:
//        ss.str("Double Clicked");
//        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 4, ss.str(), 0x59);
//        break;        
//    case MOUSE_WHEELED:
//        if (g_mouseEvent.buttonState & 0xFF000000)
//            ss.str("Mouse wheeled down");
//        else
//            ss.str("Mouse wheeled up");
//        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 5, ss.str(), 0x59);
//        break;
//    default:        
//        break;
//    }
//    
//}