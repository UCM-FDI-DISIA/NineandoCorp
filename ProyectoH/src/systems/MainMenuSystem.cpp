#include "MainMenuSystem.h"
#include "../ecs/Manager.h"

MainMenuSystem::MainMenuSystem() {

}

MainMenuSystem::~MainMenuSystem() {

}

void MainMenuSystem::initSystem() {
	/*Entity* e = mngr_->addEntity(_grp_HUD_BACKGROUND);
	Transform* tr = mngr_->addComponent<Transform>(e);
	Vector2D v = new Vector2D(1200, 800);
	tr->setScale(v);
	mngr_->addComponent<RenderComponent>(e, gameTextures::square);*/

	Entity* b = mngr_->addEntity(_grp_HUD_FOREGROUND);
	Transform* tr = mngr_->addComponent<Transform>(b);
	
	mngr_->addComponent<RenderComponent>(b, play);
	ButtonComponent* bC = mngr_->addComponent<ButtonComponent>(b, pruebaButton);
	bC->setHover(gameTextures::playHover);
	bC->setTexture(gameTextures::play);

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