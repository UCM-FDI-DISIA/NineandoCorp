#include "GameStateMachine.h"

// Constructor
GameStateMachine::GameStateMachine() {}

// Destructor
GameStateMachine::~GameStateMachine() {
    clearStates();
    clearStatesToErase();
}

// Adds state
void GameStateMachine::pushState(GameState* newState) { 
     gameStates.push_back(newState); 
}

// Erases state
void GameStateMachine::popState() {
    gameStatesToErase.push_back(gameStates.back());
    gameStates.pop_back(); 
}

// Erases every state on the stack
void GameStateMachine::clearStates() {
    while (!gameStates.empty()) popState();
}

// Return current state
GameState* GameStateMachine::currentState() { return gameStates.back(); }

// Changes the current state
void GameStateMachine::changeState(GameState* newState) {
    clearStates();
    pushState(newState);
}

// Clears the game states to erase stack
void GameStateMachine::clearStatesToErase() {
    while (!gameStatesToErase.empty()){
        delete(gameStatesToErase.front());
        gameStatesToErase.pop_front();
    }
}


// Calls current state handleInput method
/*void GameStateMachine::handleInput() {
    currentState()->handleInput();
}*/
// Calls current state update method
void GameStateMachine::update() {
    clearStatesToErase();
    for (GameState* state : gameStates) {
        state->refresh();
    }
    currentState()->update();
}