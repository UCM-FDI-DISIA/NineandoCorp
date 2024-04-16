
#include "ConfigState.h"

ConfigState::ConfigState(Manager* mngr) : GameState(_gmStt_CONFIG, mngr)
{
	mngr_->removeSystem<ButtonSystem>();
	mngr_->removeSystem<MainMenuSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_CONFIG);
	mngr_->addSystem<ConfigSystem>();
}

ConfigState::~ConfigState() {
	mngr_->removeSystem<ButtonSystem>();
	mngr_->removeSystem<ConfigSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_MAIN);
	mngr_->addSystem<MainMenuSystem>();
}
