#ifndef GAME_STATE_MACHINE_H_
#define GAME_STATE_MACHINE_H_
#include <list>
#include "GameState.h"
using namespace std;

class GameStateMachine {
private:
    list<GameState*> gameStates;
    list<GameState*> gameStatesToErase;
   
public:
    // Constructor
    GameStateMachine();
    // Destructor
    ~GameStateMachine();
    // Adds state
    void pushState(GameState* newState);
    // Erases state
    void popState();
    // Erases every state on the stack
    void clearStates();
    // Return current state
    GameState* currentState();
    // Changes the current state
    void changeState(GameState* newState);
    // Clears the game states to erase stack
    void clearStatesToErase();
    // Update Cursor image
    

    // Calls current state update method
    void update();
};
#endif
