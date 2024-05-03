#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState(int level_, int turrentLevels[]) : GameState(_gmStt_PLAY), level(level_) {

	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<MainControlSystem>(level);
	
	auto map = mngr_->addSystem<mapSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_PLAY);
	mngr_->addSystem<HUDSystem>();
	mngr_->addSystem<TowerSystem>();
	mngr_->addSystem<EnemySystem>();
	mngr_->addSystem<CollisionSystem>();
	mngr_->addSystem<ParticleSystem>();
	mngr_->addSystem<MeteorologySystem>();
	SDL_Rect* offset = mngr_->addSystem<RenderSystem>()->getOffset();

	Message m;
	m.id = _m_START_GAME;
	m.start_game_data.money = 150; //Dinero inicial 150
	m.start_game_data.cameraOffset = offset;
	m.start_game_data.netmap = map->getMalla();
	m.start_game_data.turrentLevels = turrentLevels;
	m.start_game_data.level = level;
	mngr_->send(m, true);

	// MUSICA
	sdlutils().musics().at("Soundtrack").setMusicVolume(game().CalculoVolumenMusica());
	sdlutils().musics().at("Soundtrack").play();
}

void PlayState::update() {
	GameState::update();
}