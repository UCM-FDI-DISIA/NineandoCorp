#include "MainMenuSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

MainMenuSystem::MainMenuSystem() {

}

MainMenuSystem::~MainMenuSystem() {

}

void MainMenuSystem::initSystem() {

	// Creación de la Imagen del Background del Menu
	/*Entity* background = mngr_->addEntity(_grp_HUD_BACKGROUND);
	Transform* tr = mngr_->addComponent<Transform>(background);
	Vector2D v = new Vector2D(1200, 800);
	tr->setScale(v);
	mngr_->addComponent<RenderComponent>(background, gameTextures::square);*/

	// Creación del Botón de Play del Menu
	Entity* playButton = mngr_->addEntity(_grp_HUD_FOREGROUND);
	mngr_->setHandler(_hdlr_BUTTON, playButton);
	Transform* tr = mngr_->addComponent<Transform>(playButton);
	tr->setScale({200, 200});
	Vector2D v = new Vector2D(sdlutils().width() / 2, sdlutils().height() / 2);
	tr->setPosition(v);
	mngr_->addComponent<RenderComponent>(playButton, gameTextures::play);
	ButtonComponent* bC = mngr_->addComponent<ButtonComponent>(playButton, playButtonMenu);	
	bC->setHover(gameTextures::playHover);
	bC->setTexture(gameTextures::play);
}

void MainMenuSystem::receive(const Message& m) {
	switch (m.id)
	{
		default:
			break;
	}
}

void MainMenuSystem::update() {

}