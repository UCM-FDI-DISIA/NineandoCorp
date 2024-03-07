#include "HUDSystem.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"

HUDSystem::HUDSystem() :
	buttonsSpace_length_(){
}
HUDSystem::~HUDSystem(){
}

void HUDSystem::initSystem() {
	buttonsSpace_length_ = sdlutils().width() - 200; 

	float heightH = (float)sdlutils().height() - 80.0f;
	//float xAux = (float)(sdlutils().width() - 150)  / 7;


	float xAux = (float)(buttonsSpace_length_ - 150 ) / 7;
	float separation = 150.0f;
	Vector2D bSize = Vector2D(100.0f, 100.0f);
	addImage({ (float)sdlutils().width() / 2 , heightH },
		{ (float)sdlutils().width() + 30.0f, 200.0f },
		0.0,
		gameTextures::box,
		_grp_HUD_BACKGROUND);

	// bullet tower
	addButton({ xAux, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addImage({ xAux, heightH },
		{ 55.0f, 80.0f }, 
		0.0, 
		gameTextures::bullet_tower_image,
		_grp_HUD_FOREGROUND);

	// cristal tower
	addButton({ xAux * 2, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addImage({ xAux * 2, heightH },
		{ 55.0f, 80.0f },
		0.0,
		gameTextures::crystal_tower_image, 
		_grp_HUD_FOREGROUND);

	//phoenix_tower
	addButton({ xAux * 3, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addImage({ xAux * 3, heightH },
		{ 60.0f, 80.0f },
		0.0,
		gameTextures::phoenix_tower_image,
		_grp_HUD_FOREGROUND);

	//dirt_tower
	addButton({ xAux * 4, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addImage({ xAux * 4, heightH },
		{ 60.0f, 80.0f },
		0.0,
		gameTextures::clay_tower_image,
		_grp_HUD_FOREGROUND);

	//sniper_tower
	addButton({ xAux * 5, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addImage({ xAux * 5, heightH },
		{ 45.0f, 80.0f },
		0.0,
		gameTextures::sniper_tower_image,
		_grp_HUD_FOREGROUND);

	//slime_tower
	addButton({ xAux * 6, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addImage({ xAux * 6, heightH },
		{ 60.0f, 80.0f },
		0.0,
		gameTextures::slime_tower_image,
		_grp_HUD_FOREGROUND);

	//boost_tower
	addButton({ xAux * 7, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addImage({ xAux * 7, heightH },
		{ 55.0f, 80.0f },
		0.0,
		gameTextures::power_tower_image,
		_grp_HUD_FOREGROUND);
}

void HUDSystem::receive(const Message& m) {

}
void HUDSystem::update() {
	manageButtons();
}

void HUDSystem::manageButtons(){
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
void HUDSystem::callFunction(ButtonTypes type, ButtonComponent* bC) {
	// Incluye la id del button para incluir 
	switch (type)
	{
	case selector_main:
		break;
	case upgrade_nexus:
		break;
	default:
		break;
	}
}
void HUDSystem::pause() {
	for (auto but : mngr_->getHandler(_hdlr_BUTTON)) {
		mngr_->getComponent<ButtonComponent>(but)->setActive(false);
	}
}

void HUDSystem::addButton(const Vector2D& pos, const Vector2D& scale, gameTextures tex, gameTextures hov, ButtonTypes type) {
	Entity* b = mngr_->addEntity(_grp_HUD_FOREGROUND);
	mngr_->setHandler(_hdlr_BUTTON, b);

	Transform* tr = mngr_->addComponent<Transform>(b);
	tr->setScale(scale);
	Vector2D aux = tr->getScale();
	tr->setPosition(pos - aux / 2);

	mngr_->addComponent<RenderComponent>(b, tex);

	ButtonComponent* bC = mngr_->addComponent<ButtonComponent>(b, type);
	bC->setTexture(tex);
	bC->setHover(hov);
}

void HUDSystem::addImage(const Vector2D& pos, const Vector2D& scale, const double rot, gameTextures t, grpId_type grpId) {
	Entity* img = mngr_->addEntity(grpId);
	Transform* tr = mngr_->addComponent<Transform>(img);
	tr->setScale(scale);
	Vector2D aux = tr->getScale();
	tr->setPosition(pos - aux / 2);
	tr->setRotation(rot);
	mngr_->addComponent<RenderComponent>(img, t);
}

