#include "MainMenuState.h"

MainMenuState::MainMenuState(int moneyToAdd) : GameState(_gmStt_MAINMENU) {

	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<MainControlSystem>();
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_MAIN);
	mngr_->addSystem<MainMenuSystem>();
	Message m;
	m.id = _m_START_MENU;
	m.money_data.Hmoney = moneyToAdd;
	mngr_->send(m);
}

MainMenuState::~MainMenuState() {
	delete mngr_;
}
