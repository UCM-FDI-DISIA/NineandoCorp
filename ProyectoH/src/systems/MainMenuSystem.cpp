#include "MainMenuSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

MainMenuSystem::MainMenuSystem() {

}

MainMenuSystem::~MainMenuSystem() {

}

void MainMenuSystem::initSystem() {
<<<<<<< Updated upstream

	// Creación de la Imagen del Background del Menu
	Entity* background = mngr_->addEntity(_grp_HUD_BACKGROUND);
	Transform* tr = mngr_->addComponent<Transform>(background);
	Vector2D v = new Vector2D(1200, 800);
	tr->setScale(v);
	mngr_->addComponent<RenderComponent>(background, gameTextures::square);
=======
	// Creación de la Imagen del Background del Menu
	/*Entity* background = mngr_->addEntity(_grp_HUD_BACKGROUND);
	Transform* tr = mngr_->addComponent<Transform>(background);
	Vector2D v = new Vector2D(1200, 800);
	tr->setScale(v);
	mngr_->addComponent<RenderComponent>(background, gameTextures::square);*/

	// Creación del Botón de Play del Menu
	Entity* playButton = mngr_->addEntity(_grp_HUD_FOREGROUND);
	Transform* tr = mngr_->addComponent<Transform>(playButton);
	Vector2D v = new Vector2D(200, 200);
	tr->setScale(v);
	v = new Vector2D(sdlutils().width() / 2, sdlutils().height() / 2);
	tr->setPosition(v);
	mngr_->addComponent<RenderComponent>(playButton, gameTextures::play);
	ButtonComponent* bC = mngr_->addComponent<ButtonComponent>(playButton, playButtonMenu);	
	bC->setHover(gameTextures::playHover);
	bC->setTexture(gameTextures::play);
>>>>>>> Stashed changes

	// Creación del Botón de Play del Menu
	Entity* playButton = mngr_->addEntity(_grp_HUD_FOREGROUND);
	tr = mngr_->addComponent<Transform>(playButton);
	v = new Vector2D(200, 200);
	tr->setScale(v);
	v = new Vector2D(sdlutils().width(), sdlutils().height());
	tr->setPosition(v);
	mngr_->addComponent<RenderComponent>(playButton, gameTextures::square);
	mngr_->addComponent<ButtonComponent>(playButton, playButtonMenu);
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