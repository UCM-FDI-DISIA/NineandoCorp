#include "LevelSelectorState.h"

LevelSelectorState::LevelSelectorState(Manager* mngr, int level_) : GameState(_gmStt_LEVELSELECTOR, mngr)
{
	mngr_->removeSystem<ButtonSystem>();
	mngr_->removeSystem<MainMenuSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_LVLSEL);
	mngr_->addSystem<LevelSelectorSystem>(level_);
}

LevelSelectorState::~LevelSelectorState(){
	mngr_->removeSystem<ButtonSystem>();
	mngr_->removeSystem<LevelSelectorSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_MAIN);
	mngr_->addSystem<MainMenuSystem>();
}
