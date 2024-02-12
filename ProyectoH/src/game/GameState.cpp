#include "GameState.h"
#include "Game.h"

#ifdef Version_2_0
// Constructor
GameState::GameState(gmSttId_type _id) : mngr_(new Manager()), id(_id) {
    mngr_->addSystem<GameCtrlSystem>();
}
#else
GameState::GameState() : mngr_(new Manager()) {}
#endif
// Destructor
GameState::~GameState() {
    delete mngr_;
}

// Updates scene's objects
void GameState::update() {
    mngr_->update();
#ifdef Version_2_0
    mngr_->flushMessages();
#endif
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