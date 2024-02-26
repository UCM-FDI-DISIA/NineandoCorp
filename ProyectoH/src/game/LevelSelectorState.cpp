#include "LevelSelectorState.h"

LevelSelectorState::LevelSelectorState(Manager* mngr) : GameState(_gmStt_LEVELSELECTOR, mngr)
{
	mngr_->removeSystem<MainMenuSystem>();
	mngr_->addSystem<LevelSelectorSystem>();
}

LevelSelectorState::~LevelSelectorState(){
	mngr_->removeSystem<LevelSelectorSystem>();
	mngr_->addSystem<MainMenuSystem>();
}
