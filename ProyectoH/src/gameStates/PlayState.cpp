#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState() : GameState(_gmStt_PLAY) {

	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<RenderSystem>();
	NetMap* net = mngr_->addSystem<mapSystem>("../ProyectoH/resources/tileMap/nivelPrueba.tmx")->getMalla();
	mngr_->addSystem<HUDSystem>();
	mngr_->addSystem<TowerSystem>(net);
	mngr_->addSystem<EnemySystem>();
}