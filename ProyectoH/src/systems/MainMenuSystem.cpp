#include "MainMenuSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

MainMenuSystem::MainMenuSystem() {

}

MainMenuSystem::~MainMenuSystem() {

}

void MainMenuSystem::initSystem() {
	//play button
	Vector2D pAux(sdlutils().width() / 2, sdlutils().height() / 2);
	Vector2D sAux(200, 200);
	addButton(pAux, sAux, gameTextures::play, gameTextures::playHover, ButtonTypes::playButtonMenu);
	//-------//
	pAux = { 200,  sdlutils().height() / 2.0f };
	sAux = { sdlutils().height() - 100.0f , 400};
	addImage(pAux, sAux, 90.0, gameTextures::box);
	//-------//
	pAux = { sdlutils().width() - 200.0f,  sdlutils().height() / 2.0f };
	sAux = { sdlutils().height() - 100.0f , 400};
	addImage(pAux, sAux, 90.0, gameTextures::box);

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
void MainMenuSystem::addButton(Vector2D pos, Vector2D scale, gameTextures tex, gameTextures hov, ButtonTypes type) {
	Entity* b = mngr_->addEntity(_grp_HUD_FOREGROUND);
	mngr_->setHandler(_hdlr_BUTTON, b);
	Transform* tr = mngr_->addComponent<Transform>(b);
	tr->setScale(scale);
	Vector2D aux =  tr->getScale();
	tr->setPosition(pos - aux / 2);
	mngr_->addComponent<RenderComponent>(b, tex);
	ButtonComponent* bC = mngr_->addComponent<ButtonComponent>(b, type);
	bC->setTexture(tex);
	bC->setHover(hov);
}

void MainMenuSystem::addImage(Vector2D pos, Vector2D scale, double rot, gameTextures t) {
	Entity* img = mngr_->addEntity(_grp_HUD_FOREGROUND);
	Transform* tr = mngr_->addComponent<Transform>(img); 
	tr->setScale(scale); 
	Vector2D aux = tr->getScale(); 
	tr->setPosition(pos - aux / 2); 
	tr->setRotation(rot);
	mngr_->addComponent<RenderComponent>(img, t);
}