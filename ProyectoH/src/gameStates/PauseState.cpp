#include "PauseState.h"
PauseState::PauseState(Manager* mngr) : GameState(_gmStt_PAUSE, mngr) {
	for (auto en : mngr_->getHandler(_hdlr_BUTTON_PLAY)) {
		mngr_->setAlive(en, false);
	}
	mngr_->deleteAllHandlers(_hdlr_BUTTON_PLAY);
	mngr_->removeSystem<HUDSystem>();
	mngr_->getSystem<ButtonSystem>()->changeButtonsIdHandler(_hdlr_BUTTON_PAUSE);
	mngr_->addSystem<PauseSystem>();
}

PauseState::~PauseState() {
	mngr_->removeSystem<PauseSystem>(); 
	mngr_->getSystem<ButtonSystem>()->changeButtonsIdHandler(_hdlr_BUTTON_PLAY);
	mngr_->getSystem<RenderSystem>()->initSystem();
	mngr_->addSystem<HUDSystem>();
}