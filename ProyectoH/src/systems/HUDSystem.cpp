#include "HUDSystem.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"
#include "../components/RenderComponent.h"

HUDSystem::HUDSystem() {

}
HUDSystem::~HUDSystem(){
}

void HUDSystem::initSystem() {

}
void HUDSystem::receive(const Message& m) {

}
void HUDSystem::update() {
	Vector2D pos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };
	//hover 
	for (auto en : mngr_->getEntities(_grp_HUD_FOREGROUND)) {
		ButtonComponent* bC = mngr_->getComponent<ButtonComponent>(en);
		if (bC->hover(pos)) mngr_->getComponent<RenderComponent>(en)->setTexture(bC->getHover());
		else  mngr_->getComponent<RenderComponent>(en)->setTexture(bC->getTexture());
	}


	if (ih().mouseButtonEvent()) {
		//Posicion actual del mouse
		

		if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1) { 

			//Recorre lista de entities de tipo HUD_FOREGROUND
			for (auto en : mngr_->getEntities(_grp_HUD_FOREGROUND)) { 

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
		funcionPrueba(en);
		break;
	case backButton:
		break;
	default:
		break;
	}
}

void HUDSystem::funcionPrueba(Transform* tr) {
	tr->addRotation(90.0);
}