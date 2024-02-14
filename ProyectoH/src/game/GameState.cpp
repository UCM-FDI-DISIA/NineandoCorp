#include "GameState.h"
#include "Game.h"

// Constructor
GameState::GameState(gmSttId_type _id) : mngr_(new Manager()), id(_id) {
    //mngr_->addSystem<GameCtrlSystem>();
}
// Destructor
GameState::~GameState() {
    delete mngr_;
}

// Updates scene's objects
void GameState::update() {
    mngr_->update();
    mngr_->flushMessages();
}

// Draws the scene on screen
void GameState::render() const {
    mngr_->render();
}

// Handles the event
void GameState::handleInput() {
    mngr_->handleInput();
}

// Clears every non alive Entity
void GameState::refresh() {
    mngr_->refresh();
}

#ifdef Version_2_0
// Sends a message to the manager
void GameState::send(const Message& m, bool delay) {
    mngr_->send(m, delay);
}
#endif