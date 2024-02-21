#include "MainMenuSystem.h"
#include "../ecs/Manager.h"

MainMenuSystem::MainMenuSystem() {

}

MainMenuSystem::~MainMenuSystem() {

}

void MainMenuSystem::initSystem() {

	// Creación de la Imagen del Background del Menu
	Entity* background = mngr_->addEntity(_grp_HUD_BACKGROUND);
	Transform* tr = mngr_->addComponent<Transform>(background);
	Vector2D v = new Vector2D(1200, 800);
	tr->setScale(v);
	mngr_->addComponent<RenderComponent>(background, gameTextures::square);

	Entity* e = mngr_->addEntity(_grp_HUD_BACKGROUND);
	Transform* tr = mngr_->addComponent<Transform>(background);
	Vector2D v = new Vector2D(1200, 800);
	tr->setScale(v);
	mngr_->addComponent<RenderComponent>(background, gameTextures::square);
}

void MainMenuSystem::receive(const Message& m) {
	/*switch (m.id)
	{
		case:
			break;
		default:
			break;
	}*/
}

void MainMenuSystem::update() {

}