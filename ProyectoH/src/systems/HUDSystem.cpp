#include "HUDSystem.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"

HUDSystem::HUDSystem() {

}
HUDSystem::~HUDSystem(){
}

void HUDSystem::initSystem() {

}
void HUDSystem::receive(const Message& m) {

}
void HUDSystem::update() {
	//Posicion actual del mouse
	Vector2D pos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };

	//hover 
	for (auto en : mngr_->getHandler(_hdlr_BUTTON)) {

		ButtonComponent* bC = mngr_->getComponent<ButtonComponent>(en);
		RenderComponent* rC = mngr_->getComponent<RenderComponent>(en);
		if (bC->hover(pos)) rC->setTexture(bC->getHover());
		else rC->setTexture(bC->getTexture());
	}


	if (ih().mouseButtonEvent()) {

		if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1) { 

			//Recorre lista de entities de tipo HUD_FOREGROUND
			for (auto en : mngr_->getHandler(_hdlr_BUTTON)) {

				//comprueba la id del button y si no es none llama a la funcion correspondiente
				auto type = mngr_->getComponent<ButtonComponent>(en)->isPressed(pos);
				if (type != ButtonTypes::none) callFunction(type, mngr_->getComponent<Transform>(en));
			}
		}
	}
}


void HUDSystem::callFunction(ButtonTypes type, Transform* en) {
	// Incluye la id del button para incluir 
	switch (type)
	{
	case pruebaButton:
		break;
	case playButtonMenu:
		loadLevelSelector();
		std::cout << "ok" << std::endl;
		break;
	case backButton:
		startLevel();
		break;
	default:
		break;
	}
}

void HUDSystem::funcionPrueba(Transform* tr) {
	tr->addRotation(90.0);
}

void HUDSystem::loadLevelSelector() {
	Message m; 
	m.id = _m_LEVEL_SELECTOR;
	mngr_->send(m);
}

void HUDSystem::startLevel() {
	Message m;
	m.id = _m_START_GAME;
	mngr_->send(m);
}

