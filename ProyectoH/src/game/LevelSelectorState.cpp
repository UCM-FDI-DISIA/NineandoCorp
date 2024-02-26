#include "LevelSelectorState.h"

LevelSelectorState::LevelSelectorState() : GameState(_gmStt_LEVELSELECTOR)
{
	mngr_->addSystem<LevelSelectorSystem>();

	mngr_->addSystem<MainControlSystem>();
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<HUDSystem>();
}
