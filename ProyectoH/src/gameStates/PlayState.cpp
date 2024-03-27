#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState() : GameState(_gmStt_PLAY) {

	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<mapSystem>("../ProyectoH/resources/tileMap/nivel");
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_PLAY);
	mngr_->addSystem<HUDSystem>();
	TowerSystem* ts = mngr_->addSystem<TowerSystem>();
	mngr_->addSystem<EnemySystem>();
	mngr_->addSystem<CollisionSystem>();
	mngr_->addSystem<ParticleSystem>();
}

void PlayState::update() {
	GameState::update();
}