#include "HUDSystem.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"

HUDSystem::HUDSystem() {

}
HUDSystem::~HUDSystem(){
}

void HUDSystem::initSystem() {
	float heightH = (float)sdlutils().height() - 190.0f;
	float separation = 150.0f;

	addImage({ (float)sdlutils().width() / 2 , heightH },
		{ (float)sdlutils().width() - 20.0f, 200.0f },
		0.0,
		gameTextures::box,
		_grp_HUD_BACKGROUND);

	addButton({ 120.0f, heightH },//bullet_tower
		{ 130.0f, 180.0f },
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addButton({ 120.0f, heightH },
		{ 100.0f, 150.0f },
		gameTextures::bullet_tower_image, gameTextures::bullet_tower_image,
		ButtonTypes::none
	);

	addButton({ 120.0f + separation, heightH },//cristal_tower
		{ 130.0f, 180.0f },
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addButton({ 120.0f + separation, heightH },
		{ 100.0f, 150.0f },
		gameTextures::cristal_tower_image, gameTextures::cristal_tower_image,
		ButtonTypes::none
	);

	addButton({ 120.0f + separation * 2, heightH },//phoenix_tower
		{ 130.0f, 180.0f },
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addButton({ 120.0f + separation * 2, heightH },
		{ 100.0f, 150.0f },
		gameTextures::phoenix_tower_image, gameTextures::phoenix_tower_image,
		ButtonTypes::none
	);

	addButton({ 120.0f + separation * 3, heightH },//dirt_tower
		{ 130.0f, 180.0f },
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addButton({ 120.0f + separation * 3, heightH },
		{ 100.0f, 150.0f },
		gameTextures::dirt_tower_image, gameTextures::dirt_tower_image,
		ButtonTypes::none
	);

	addButton({ 120.0f + separation * 4, heightH },//sniper_tower
		{ 130.0f, 180.0f },
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addButton({ 120.0f + separation * 4, heightH },
		{ 100.0f, 150.0f },
		gameTextures::sniper_tower_image, gameTextures::sniper_tower_image,
		ButtonTypes::none
	);

	addButton({ 120.0f + separation * 5, heightH },//slime_tower
		{ 130.0f, 180.0f },
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addButton({ 120.0f + separation * 5, heightH },
		{ 100.0f, 150.0f },
		gameTextures::slime_tower_image, gameTextures::slime_tower_image,
		ButtonTypes::none
	);

	addButton({ 120.0f + separation * 6, heightH },//boost_tower
		{ 130.0f, 180.0f },
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addButton({ 120.0f + separation * 6, heightH },
		{ 100.0f, 150.0f },
		gameTextures::power_tower_image, gameTextures::power_tower_image,
		ButtonTypes::none
	);
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

