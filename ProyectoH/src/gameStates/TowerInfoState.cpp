#include "TowerInfoState.h"

TowerInfoState::TowerInfoState(Manager* mngr, twrId tId) : GameState(_gmStt_INFO, mngr) {
	mngr_->removeSystem<MainMenuSystem>();
	mngr_->getSystem<ButtonSystem>()->changeButtonsIdHandler(_hdlr_BUTTON_INFO);
	mngr_->addSystem<TowerInfoSystem>(tId);
}

TowerInfoState::~TowerInfoState() {
	mngr_->removeSystem<TowerInfoSystem>();
	mngr_->getSystem<ButtonSystem>()->changeButtonsIdHandler(_hdlr_BUTTON_MAIN);
	mngr_->addSystem<MainMenuSystem>();
}
