
#include "EnemyBookState.h"

EnemyBookState::EnemyBookState(Manager* mngr) : GameState(_gmStt_LEVELSELECTOR, mngr)
{
	mngr_->removeSystem<ButtonSystem>();
	mngr_->removeSystem<MainMenuSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_ENEMYBOOK);
	mngr_->addSystem<LevelSelectorSystem>();
}

EnemyBookState::~EnemyBookState() {
	mngr_->removeSystem<ButtonSystem>();
	mngr_->removeSystem<LevelSelectorSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_ENEMYBOOK);
	mngr_->addSystem<MainMenuSystem>();
}
