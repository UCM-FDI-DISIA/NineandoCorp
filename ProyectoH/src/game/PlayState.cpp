#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState() : GameState(_gmStt_PLAY) {
	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<RenderSystem>();
	//mngr_->addSystem<mapSystem>("../ProyectoH/resources/tileMap/nivelPrueba.tmx");

	/*Entity* t = new Entity(_grp_TOWERS);*/

	//mngr_->addComponent<AttackComponent>(t);
	//mngr_->addComponent<RenderComponent>(t);

	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<mapSystem>("../ProyectoH/resources/tileMap/nivelPrueba.tmx");

}

void PlayState::update() {
	GameState::update();
}