
#include "EnemyBookState.h"

EnemyBookState::EnemyBookState(Manager* mngr) : GameState(_gmStt_ENEMYBOOK, mngr)
{
	mngr_->removeSystem<ButtonSystem>();
	mngr_->removeSystem<MainMenuSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_ENEMYBOOK);
	mngr_->addSystem<EnemyBookSystem>();
}

EnemyBookState::~EnemyBookState() {
	mngr_->removeSystem<ButtonSystem>();
	mngr_->removeSystem<EnemyBookSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_ENEMYBOOK);
	mngr_->addSystem<MainMenuSystem>();
}
