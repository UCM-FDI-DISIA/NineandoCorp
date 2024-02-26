#include "GameState.h"
#include "Game.h"

// Constructor
GameState::GameState(gmSttId_type _id, Manager* m = nullptr) : id(_id) {
    if (m == nullptr)
        mngr_ = new Manager();
}
// Destructor
GameState::~GameState() {
}

// Updates scene's objects
void GameState::update() {
    mngr_->update();
    mngr_->flushMessages();
}

// Clears every non alive Entity
void GameState::refresh() {
    mngr_->refresh();
}

// Sends a message to the manager
void GameState::send(const Message& m, bool delay) {
    mngr_->send(m, delay);
}