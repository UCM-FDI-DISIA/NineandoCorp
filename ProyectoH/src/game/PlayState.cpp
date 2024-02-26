#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState(Manager* mngr) : GameState(_gmStt_PLAY, mngr) {
	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<mapSystem>("../ProyectoH/resources/tileMap/nivelPrueba.tmx");

}

void PlayState::update() {
	GameState::update();
}