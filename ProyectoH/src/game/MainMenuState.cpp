#include "MainMenuState.h"

MainMenuState::MainMenuState() : GameState(_gmStt_MAINMENU) {
	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<MainMenuSystem>();
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<mapSystem>("../ProyectoH/resources/tileMap/nivelPrueba.tmx");
}
