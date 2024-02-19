#include "HUDSystem.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"

HUDSystem::HUDSystem() {

}

void HUDSystem::initSystem() {

}
void HUDSystem::receive(const Message& m) {

}
void HUDSystem::update() {
	if (ih().mouseButtonEvent()) {
		//Posicion actual del mouse
		Vector2D pos = { ih().getMousePos().first, ih().getMousePos().second };

		if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1) { 

			//Recorre lista de entities de tipo HUD_FOREGROUND
			for (auto en : mngr_->getEntities(_grp_HUD_FOREGROUND)) { 

				//comprueba la id del button y si no es none llama a la funcion correspondiente
				auto type = mngr_->getComponent<ButtonComponent>(en)->isPressed(pos);
				if (type != ButtonTypes::none) callFunction(type);
			}
		}
	}
}


void HUDSystem::callFunction(ButtonTypes type) {
	// Incluye la id del button para incluir 
	switch (type)
	{
	case pruebaButton:
		break;
	case backButton:
		break;
	default:
		break;
	}
}