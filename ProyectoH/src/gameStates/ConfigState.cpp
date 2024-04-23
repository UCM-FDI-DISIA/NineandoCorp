
#include "ConfigState.h"

ConfigState::ConfigState(Manager* mngr, bool isPlayState) : GameState(_gmStt_CONFIG, mngr), isPlayState(isPlayState)
{
	if(!isPlayState)
		mngr_->removeSystem<MainMenuSystem>();
	else
		mngr_->removeSystem<PauseSystem>();
	mngr_->getSystem<ButtonSystem>()->changeButtonsIdHandler(_hdlr_BUTTON_CONFIG);
	mngr_->addSystem<ConfigSystem>(isPlayState);
}

ConfigState::~ConfigState() {
	mngr_->removeSystem<ConfigSystem>();
	if (isPlayState) {
		mngr_->getSystem<ButtonSystem>()->changeButtonsIdHandler(_hdlr_BUTTON_PLAY);
		mngr_->addSystem<PauseSystem>();
	}
	else {
		mngr_->getSystem<ButtonSystem>()->changeButtonsIdHandler(_hdlr_BUTTON_MAIN);
		mngr_->addSystem<MainMenuSystem>();
	}
	
}
