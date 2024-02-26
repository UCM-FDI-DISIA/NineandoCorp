#include "LevelSelectorSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

LevelSelectorSystem::LevelSelectorSystem()
{
}

LevelSelectorSystem::~LevelSelectorSystem()
{
	for (auto en : mngr_->getHandler(_hdlr_SUBMENU)) {
		mngr_->setAlive(en, false);
	}
	mngr_->deleteAllHandlers(_hdlr_SUBMENU);
	mngr_->deleteHandler(_hdlr_BUTTON, backButtonEntity);
}

void LevelSelectorSystem::initSystem()
{
	//play button
	Vector2D pAux(sdlutils().width() / 2, (sdlutils().height() / 2) + 350);
	Vector2D sAux(350, 110);
	backButtonEntity = addButton(pAux, sAux, gameTextures::play, gameTextures::play_hover, ButtonTypes::backButton);
	//-------//
	pAux = { 800,  800 };
	sAux = { sdlutils().height() - 100.0f , 400 };
	addImage(pAux, sAux, 90.0, gameTextures::box);
}

void LevelSelectorSystem::receive(const Message& m)
{
	switch (m.id)
	{
	default:
		break;
	}
}

void LevelSelectorSystem::update() {
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

void LevelSelectorSystem::callFunction(ButtonTypes type, ButtonComponent* bC) {
	// Incluye la id del button para incluir 
	switch (type)
	{
	case backButton:
		backToMainMenu();
		break;
	default:
		break;
	}
}

Entity* LevelSelectorSystem::addButton(Vector2D pos, Vector2D scale, gameTextures tex, gameTextures hov, ButtonTypes type)
{
	Entity* b = mngr_->addEntity(_grp_HUD_FOREGROUND);
	mngr_->setHandler(_hdlr_BUTTON, b);
	mngr_->setHandler(_hdlr_SUBMENU, b);
	Transform* tr = mngr_->addComponent<Transform>(b);
	tr->setScale(scale);
	Vector2D aux = tr->getScale();
	tr->setPosition(pos - aux / 2);

	mngr_->addComponent<RenderComponent>(b, tex);

	ButtonComponent* bC = mngr_->addComponent<ButtonComponent>(b, type);
	bC->setTexture(tex);
	bC->setHover(hov);
	return b;
}

void LevelSelectorSystem::addImage(Vector2D pos, Vector2D(scale), double rot, gameTextures t)
{
	Entity* img = mngr_->addEntity(_grp_HUD_FOREGROUND);
	mngr_->setHandler(_hdlr_SUBMENU, img);
	Transform* tr = mngr_->addComponent<Transform>(img);
	tr->setScale(scale);
	Vector2D aux = tr->getScale();
	tr->setPosition(pos - aux / 2);
	tr->setRotation(rot);
	mngr_->addComponent<RenderComponent>(img, t);
}

void LevelSelectorSystem::backToMainMenu() {
	Message m;
	m.id = _m_BACK_TO_MAINMENU;
	mngr_->send(m);
}



