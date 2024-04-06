#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState(Manager* mngr) : GameState(_gmStt_PLAY, mngr) {

	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_PLAY);
	mngr_->addSystem<EnemySystem>();
	mngr_->addSystem<CollisionSystem>();
	mngr_->addSystem<ParticleSystem>();
	mngr_->addSystem<MeteorologySystem>();

	Message m;
	m.id = _m_START_GAME;
	mngr_->send(m, true);
}

void PlayState::update() {
	GameState::update();
}