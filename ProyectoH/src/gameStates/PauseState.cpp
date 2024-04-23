#include "PauseState.h"
PauseState::PauseState(Manager* mngr) : GameState(_gmStt_PAUSE, mngr) {
	mngr_->removeSystem<HUDSystem>();
	mngr_->addSystem<PauseSystem>();
}

PauseState::~PauseState() {
	mngr_->removeSystem<PauseSystem>();
	mngr_->addSystem<HUDSystem>();
}