
#include "ConfigState.h"

ConfigState::ConfigState(Manager* mngr) : GameState(_gmStt_CONFIG, mngr)
{
	mngr_->removeSystem<MainMenuSystem>();
	mngr_->getSystem<ButtonSystem>()->changeButtonsIdHandler(_hdlr_BUTTON_CONFIG);
	mngr_->addSystem<ConfigSystem>();
}

ConfigState::~ConfigState() {
	mngr_->removeSystem<ConfigSystem>();
	mngr_->getSystem<ButtonSystem>()->changeButtonsIdHandler(_hdlr_BUTTON_MAIN);
	mngr_->addSystem<MainMenuSystem>();
}
