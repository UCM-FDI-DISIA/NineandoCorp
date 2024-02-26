#include "LevelSelectorState.h"

LevelSelectorState::LevelSelectorState(Manager* mngr) : GameState(_gmStt_LEVELSELECTOR, mngr)
{
	mngr_->addSystem<LevelSelectorSystem>();

	mngr_->addSystem<MainControlSystem>();
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<HUDSystem>();
}

LevelSelectorState::~LevelSelectorState(){
	mngr_->removeSystem<LevelSelectorSystem>();
	//mngr_->removeSystem<MainControlSystem>();
	//mngr_->removeSystem<RenderSystem>();
	//mngr_->removeSystem<HUDSystem>();
}
