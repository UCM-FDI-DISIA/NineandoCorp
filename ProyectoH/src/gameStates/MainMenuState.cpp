#include "MainMenuState.h"

MainMenuState::MainMenuState(Manager* mngr) : GameState(_gmStt_MAINMENU, mngr) {
	// Sistemas requeridos para que funcione el juego


	mngr_->addSystem<MainControlSystem>();
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_MAIN);
	mngr_->addSystem<MainMenuSystem>();
}

MainMenuState::~MainMenuState() {

}
