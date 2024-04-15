#include "GameOverSystem.h"
#include "ButtonSystem.h"
#include "../ecs/Manager.h"

GameOverSystem::GameOverSystem() {
}

void GameOverSystem::initSystem() {
	float xAux = 200;
	float heightH = 200;
	Vector2D bSize = { 100, 100 };

	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();

	bS->addImage({ -(float)sdlutils().width()/2 , -(float)sdlutils().height()/2 },
		{ (float)sdlutils().width(), (float)sdlutils().height() },
		0.0,
		gameTextures::box,
		_grp_HUD_BACKGROUND);

	bS->addButton({ xAux, heightH },
		bSize,
		gameTextures::backToMenu_button, gameTextures::backToMenu_button_hover,
		ButtonTypes::bullet_drag);
}

GameOverSystem::~GameOverSystem() {

}