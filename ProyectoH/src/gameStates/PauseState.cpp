#include "PauseState.h"
PauseState::PauseState(Manager* mngr) : GameState(_gmStt_PAUSE, mngr) {
	mngr_->addSystem<PauseSystem>();
}

PauseState::~PauseState() {
	mngr_->removeSystem<PauseSystem>();
}