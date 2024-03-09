#include "ButtonSystem.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"

ButtonSystem::ButtonSystem(hdlrId_type but_id) : 
	hdlr_but_id(but_id){
}

ButtonSystem::~ButtonSystem(){
}
void ButtonSystem::update() {
	manageButtons();
}


void ButtonSystem::initSystem() {
}
void ButtonSystem::receive(const Message& m){
}


void ButtonSystem::manageButtons() {
	//Posicion actual del mouse
	Vector2D pos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };

	//hover 
	for (auto en : mngr_->getHandler(hdlr_but_id)) {
		if (en != nullptr) {

			ButtonComponent* bC = mngr_->getComponent<ButtonComponent>(en);
			RenderComponent* rC = mngr_->getComponent<RenderComponent>(en);
			if (bC != nullptr) {
				if (bC->isActive()) {
					if (bC->hover(pos)) rC->setTexture(bC->getHover());
					else rC->setTexture(bC->getTexture());
				}
			}
		}
	}

	//click
	if (ih().mouseButtonEvent()) {

		if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1) {

			//Recorre lista de entities de tipo HUD_FOREGROUND
			for (auto en : mngr_->getHandler(hdlr_but_id)) {
				auto bC = mngr_->getComponent<ButtonComponent>(en);
				if (en != nullptr && bC != nullptr) {
					//comprueba la id del button y si no es none llama a la funcion correspondiente
					auto type = bC->isPressed(pos);
					if (type != ButtonTypes::none) callFunction(type, en);
				}
			}
		}
	}
}

#pragma region FUNCIONES DE BOTONES

	//Todas las funciones de los botones del juego
	void ButtonSystem::callFunction(ButtonTypes type, Entity* bC) {
		// Incluye la id del button para incluir 
		switch (type)
		{
		case selector_main:
			loadLevelSelector();
			pauseAllButtons();
			break;
		case back_selector:
			backToMainMenu();
			break;
		case start_game:
			startGame();
			break;
		case crystal_drag:
			break;
		case upgrade_nexus:
			break;
		default:
			break;
		}
	}
	void ButtonSystem::pauseAllButtons() {
		for (auto but : mngr_->getHandler(hdlr_but_id)) {
			auto bC = mngr_->getComponent<ButtonComponent>(but);
			if(bC != nullptr) bC->setActive(false);
		}
	}
	void ButtonSystem::loadLevelSelector() {
		Message m;
		m.id = _m_LEVEL_SELECTOR;
		mngr_->send(m, true);
	}
	void ButtonSystem::backToMainMenu() {
		Message m;
		m.id = _m_BACK_TO_MAINMENU;
		mngr_->send(m);
	}
	void ButtonSystem::startGame() {
		Message m;
		m.id = _m_START_GAME;
		mngr_->send(m);
	}

	void ButtonSystem::dragTower(twrId tower) {
		Message m;
		m.id = _m_DRAG;
		m.drag_data.towerId = tower;
		mngr_->send(m);
	}
#pragma endregion


Entity* ButtonSystem::addButton(const Vector2D& pos, const Vector2D& scale, gameTextures tex, gameTextures hov, ButtonTypes type) {
	Entity* b = mngr_->addEntity(_grp_HUD_FOREGROUND);
	mngr_->setHandler(hdlr_but_id, b);

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

void ButtonSystem::addImage(const Vector2D& pos, const Vector2D& scale, const double rot, gameTextures t, grpId_type grpId) {
	Entity* img = mngr_->addEntity(grpId);
	mngr_->setHandler(hdlr_but_id, img);
	Transform* tr = mngr_->addComponent<Transform>(img);
	tr->setScale(scale);
	Vector2D aux = tr->getScale();
	tr->setPosition(pos - aux / 2);
	tr->setRotation(rot);
	mngr_->addComponent<RenderComponent>(img, t);
}
