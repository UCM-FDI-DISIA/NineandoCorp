#include "MainMenuState.h"

MainMenuState::MainMenuState(Manager* mngr) : GameState(_gmStt_MAINMENU, mngr) {
	// Sistemas requeridos para que funcione el juego

	mngr_->addSystem<MainMenuSystem>();

	mngr_->addSystem<MainControlSystem>();
	mngr_->addSystem<RenderSystem>();
}

MainMenuState::~MainMenuState() {
	mngr_->deleteAllHandlers(_hdlr_BUTTON);
	//borramos background
	for (auto en : mngr_->getEntities(_grp_HUD_BACKGROUND)) {
		mngr_->setAlive(en, false);
	}
	for (auto en : mngr_->getEntities(_grp_HUD_FOREGROUND)) {
		mngr_->setAlive(en, false);
	}
}
