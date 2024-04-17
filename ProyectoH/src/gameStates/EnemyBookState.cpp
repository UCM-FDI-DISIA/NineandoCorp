
#include "EnemyBookState.h"

EnemyBookState::EnemyBookState(Manager* mngr) : GameState(_gmStt_ENEMYBOOK, mngr)
{
	mngr_->removeSystem<MainMenuSystem>();
	mngr_->getSystem<ButtonSystem>()->changeButtonsIdHandler(_hdlr_BUTTON_ENEMYBOOK);
	mngr_->addSystem<EnemyBookSystem>();
}

EnemyBookState::~EnemyBookState() {
	mngr_->removeSystem<EnemyBookSystem>();
	mngr_->getSystem<ButtonSystem>()->changeButtonsIdHandler(_hdlr_BUTTON_MAIN);
	mngr_->addSystem<MainMenuSystem>();
}
