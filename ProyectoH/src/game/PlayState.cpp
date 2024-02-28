#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState() : GameState(_gmStt_PLAY) {

	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<mapSystem>("../ProyectoH/resources/tileMap/nivelPrueba.tmx");
	mngr_->addSystem<HUDSystem>();

}

void PlayState::update() {
	GameState::update();
}