#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState() : GameState(_gmStt_PLAY) {

	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<RenderSystem>();
	std::vector<std::vector<casilla>>* malla = mngr_->addSystem<mapSystem>("../ProyectoH/resources/tileMap/nivelPrueba.tmx")->getMalla();
	mngr_->addSystem<HUDSystem>();
	mngr_->addSystem<TowerSystem>(malla);
	mngr_->addSystem<EnemySystem>();
}