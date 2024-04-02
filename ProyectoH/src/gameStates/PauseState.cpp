#include "PauseState.h"
PauseState::PauseState(Manager* mngr) : GameState(_gmStt_PAUSE, mngr) {
	// Sistemas requeridos para que funcione el juego

	mngr_->removeSystem<ButtonSystem>();
	mngr_->removeSystem<HUDSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_PAUSE);
	//mngr_->addSystem<PauseSystem>();
}

PauseState::~PauseState() {
	mngr_->removeSystem<ButtonSystem>();
	mngr_->removeSystem<PauseSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_PAUSE);
	mngr_->addSystem<HUDSystem>();
}