#include "MainMenuState.h"

MainMenuState::MainMenuState() : GameState(_gmStt_MAINMENU) {

	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<MainControlSystem>(game().getSaveGame()->getLevelsUnlocked());
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_MAIN);
	mngr_->addSystem<ParticleSystem>();
	mngr_->addSystem<MainMenuSystem>();
	Message m;
	m.id = _m_START_MENU;
	m.money_data.money = game().getSaveGame()->getHCoins();
	mngr_->send(m);

	// MUSICA
	sdlutils().musics().at("MenuSoundtrack").setMusicVolume(game().CalculoVolumenMusica());
	sdlutils().musics().at("MenuSoundtrack").play();
}

MainMenuState::~MainMenuState() {
	delete mngr_;
}
