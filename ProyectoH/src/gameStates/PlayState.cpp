#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState() : GameState(_gmStt_PLAY) {

	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<RenderSystem>();
	NetMap* net = mngr_->addSystem<mapSystem>("../ProyectoH/resources/tileMap/nivelPrueba.tmx")->getMalla();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_PLAY);
	mngr_->addSystem<HUDSystem>();
	TowerSystem* ts = mngr_->addSystem<TowerSystem>();
	mngr_->addSystem<EnemySystem>();
	mngr_->addSystem<CollisionSystem>();
}

void PlayState::update() {
	GameState::update();
}