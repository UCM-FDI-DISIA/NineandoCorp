#include "MainMenuState.h"

MainMenuState::MainMenuState(Manager* mngr) : GameState(_gmStt_MAINMENU, mngr) {
	// Sistemas requeridos para que funcione el juego


	mngr_->addSystem<MainControlSystem>();
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_MAIN);
<<<<<<< Updated upstream
	mngr_->addSystem<MainMenuSystem>();
=======
	MainMenuSystem* mms = mngr_->addSystem<MainMenuSystem>();
	Message m;
	m.id = _m_START_MENU;
	m.money_data.money = game().getSaveGame()->getHCoins();

	mngr_->send(m);
>>>>>>> Stashed changes
}

MainMenuState::~MainMenuState() {
	delete mngr_;
}
