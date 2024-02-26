#include "MainMenuState.h"

MainMenuState::MainMenuState(Manager* mngr) : GameState(_gmStt_MAINMENU, mngr) {
	// Sistemas requeridos para que funcione el juego

	mngr_->addSystem<MainMenuSystem>();

	mngr_->addSystem<MainControlSystem>();
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<HUDSystem>();
}
