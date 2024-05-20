#include "PauseState.h"
PauseState::PauseState(Manager* mngr) : GameState(_gmStt_PAUSE, mngr) {
	mngr_->getSystem<ButtonSystem>()->changeButtonsIdHandler(_hdlr_BUTTON_PAUSE);
	mngr_->addSystem<PauseSystem>();
}

PauseState::~PauseState() {
	mngr_->removeSystem<PauseSystem>(); 
	mngr_->getSystem<ButtonSystem>()->changeButtonsIdHandler(_hdlr_BUTTON_PLAY);
	mngr_->getSystem<RenderSystem>()->initSystem();
	mngr_->addSystem<HUDSystem>();
}