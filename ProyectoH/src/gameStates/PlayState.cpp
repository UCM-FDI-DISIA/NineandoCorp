#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState() : GameState(_gmStt_PLAY) {

	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<MainControlSystem>();
	SDL_Rect* offset = mngr_->addSystem<RenderSystem>()->getOffset();
	auto map = mngr_->addSystem<mapSystem>("../ProyectoH/resources/tileMap/nivel");
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_PLAY);
	mngr_->addSystem<HUDSystem>();
	mngr_->addSystem<TowerSystem>();
	mngr_->addSystem<EnemySystem>();
	mngr_->addSystem<CollisionSystem>();
	mngr_->addSystem<ParticleSystem>();
	mngr_->addSystem<MeteorologySystem>();

	Message m;
	m.id = _m_START_GAME;
	m.start_game_data.money = 15000;
	m.start_game_data.cameraOffset = offset;
	m.start_game_data.netmap = map->getMalla();
	m.start_game_data.level = 1;
	mngr_->send(m, true);
}

void PlayState::update() {
	GameState::update();
}