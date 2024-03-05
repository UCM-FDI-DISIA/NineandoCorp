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
	mngr_->deleteHandler(_hdlr_BUTTON, playButtonEntity);
}

void LevelSelectorSystem::initSystem()
{
	//-------//
	Vector2D pAux = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
	Vector2D sAux = {  1000.0f , 600.0f };
	addImage(pAux, sAux, 0.0, gameTextures::large_box);

	//close button
	pAux = pAux + Vector2D(430.0f, -230.0f);
	sAux = { 70.0f, 70.0f };
	backButtonEntity = addButton(pAux, sAux, gameTextures::close, gameTextures::close_hover, ButtonTypes::back_selector);

	//play button
	pAux = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
	sAux = { 350, 110 };
	playButtonEntity = addButton(pAux, sAux, gameTextures::play, gameTextures::play_hover, ButtonTypes::start_game);
	
}

void LevelSelectorSystem::receive(const Message& m)
{
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
	case back_selector:
		backToMainMenu();
		break;
	case start_game:
		startGame();
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
void LevelSelectorSystem::startGame() {
	Message m;
	m.id = _m_START_GAME;
	mngr_->send(m);
}



