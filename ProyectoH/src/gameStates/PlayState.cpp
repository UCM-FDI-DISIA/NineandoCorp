#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState(int level_, vector<int>& turrentLevels) : GameState(_gmStt_PLAY), level(level_) {

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
	m.start_game_data.turrentLevels = &turrentLevels;
	m.start_game_data.level = level;
	mngr_->send(m, true);

	// Inicialización del Nexo
	Message m2;
	m2.id = _m_ADD_TOWER;
	m2.add_tower_data.towerId = _twr_NEXUS;
	m2.add_tower_data.pos = { 580.0f, 980.0f };
	m2.add_tower_data.height = BOTH;
	m2.add_tower_data.maxLvl = turrentLevels[_twr_NEXUS];

}

void PlayState::update() {
	GameState::update();
}