#include "PlayState.h"
#include "../game/Game.h"
#include "../components/ButtonComponent.h"
#include "../components/Transform.h"
#include "../components/RenderComponent.h"

PlayState::PlayState() : GameState(_gmStt_PLAY) {
	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<RenderSystem>();
	//mngr_->addSystem<mapSystem>("../ProyectoH/resources/tileMap/nivelPrueba.tmx");
	mngr_->addSystem<HUDSystem>();
	
	mngr_->addEntity(_grp_HUD_FOREGROUND);
	for (auto& b : mngr_->getEntities(_grp_HUD_FOREGROUND)) {
		mngr_->addComponent<Transform>(b);
		mngr_->addComponent<ButtonComponent>(b, ButtonTypes::pruebaButton);
		mngr_->addComponent<RenderComponent>(b, gameTextures::square);
	}
}

void PlayState::handleInput() {
	
}

void PlayState::update() {
	GameState::update();
}