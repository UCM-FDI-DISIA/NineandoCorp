#include "MainMenuSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

MainMenuSystem::MainMenuSystem() {

}

MainMenuSystem::~MainMenuSystem() {
	
}

void MainMenuSystem::initSystem() {
	//play button
	Vector2D pAux(sdlutils().width() / 2, (sdlutils().height() / 2) + 150);
	Vector2D sAux(350, 110);
	addButton(pAux, sAux , gameTextures::play, gameTextures::play_hover, ButtonTypes::playButtonMenu);
	//-------//
	pAux = { 200,  sdlutils().height() / 2.0f };
	sAux = { sdlutils().height() - 100.0f , 400};
	addImage(pAux, sAux, 90.0, gameTextures::box, _grp_HUD_BACKGROUND);
	//-------//
	pAux = { sdlutils().width() - 200.0f,  sdlutils().height() / 2.0f };
	sAux = { sdlutils().height() - 100.0f , 400};
	addImage(pAux, sAux, 90.0, gameTextures::box, _grp_HUD_BACKGROUND);

}

void MainMenuSystem::receive(const Message& m) {
	switch (m.id)
	{
		default:
			break;
	}
}

void MainMenuSystem::update() {
	//Posicion actual del mouse
	Vector2D pos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };

	//hover 
	for (auto en : mngr_->getHandler(_hdlr_BUTTON)) {
		if (en != nullptr) {

			ButtonComponent* bC = mngr_->getComponent<ButtonComponent>(en);
			RenderComponent* rC = mngr_->getComponent<RenderComponent>(en);
			if (bC->isActive()) {
				if (bC->hover(pos)) rC->setTexture(bC->getHover());
				else rC->setTexture(bC->getTexture());
			}
		}
	}


	if (ih().mouseButtonEvent()) {

		if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1) {

			//Recorre lista de entities de tipo HUD_FOREGROUND
			for (auto en : mngr_->getHandler(_hdlr_BUTTON)) {
				if (en != nullptr) {
					//comprueba la id del button y si no es none llama a la funcion correspondiente
					auto type = mngr_->getComponent<ButtonComponent>(en)->isPressed(pos);
					if (type != ButtonTypes::none) callFunction(type, mngr_->getComponent<ButtonComponent>(en));
				}
			}
		}
	}
}


void MainMenuSystem::callFunction(ButtonTypes type, ButtonComponent* bC) {
	// Incluye la id del button para incluir 
	switch (type)
	{
	case pruebaButton:
		break;
	case playButtonMenu:
		loadLevelSelector();
		bC->setActive(false);
		break;
	default:
		break;
	}
}

void MainMenuSystem::funcionPrueba(Transform* tr) {
	tr->addRotation(90.0);
}

void MainMenuSystem::loadLevelSelector() {
	Message m;
	m.id = _m_LEVEL_SELECTOR;
	mngr_->send(m,true);
}

void MainMenuSystem::startLevel() {
	Message m;
	m.id = _m_START_GAME;
	mngr_->send(m);
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

void MainMenuSystem::addImage(Vector2D pos, Vector2D scale, double rot, gameTextures t, grpId_type grpId) {
	Entity* img = mngr_->addEntity(grpId);
	Transform* tr = mngr_->addComponent<Transform>(img); 
	tr->setScale(scale); 
	Vector2D aux = tr->getScale(); 
	tr->setPosition(pos - aux / 2); 
	tr->setRotation(rot);
	mngr_->addComponent<RenderComponent>(img, t);
}