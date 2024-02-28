#include "MainMenuSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

MainMenuSystem::MainMenuSystem() {

}

MainMenuSystem::~MainMenuSystem() {
	
}

void MainMenuSystem::initSystem() {

	// cleon: creais mucho reuido con las variables locales.
	// al menos, redefinid cada una por pseparado (no reutiliceis "pAux")

	// BACKGROUND
	addImage({ sdlutils().width() / 2.0f, (sdlutils().height() / 2.0f) },
		{ 1200 , 900 }, 
		0.0, gameTextures::box, _grp_HUD_BACKGROUND);

	// LOGO
	addImage({ sdlutils().width() / 2.0f, (sdlutils().height() / 2.0f)  - 250},
		{ 213 , 159 },
		0.0, gameTextures::logo, _grp_HUD_BACKGROUND);

	// LEFT COLUMN
	addImage({ 200,  sdlutils().height() / 2.0f }, 
		{ sdlutils().height() - 100.0f , 400 },
		90.0, gameTextures::box, _grp_HUD_BACKGROUND);
	// RIGHT COLUMN
	addImage({ sdlutils().width() - 200.0f,  sdlutils().height() / 2.0f },
		{ sdlutils().height() - 100.0f , 400 },
		90.0, gameTextures::box, _grp_HUD_BACKGROUND);

	//-------------------------------------------//

	// ENEMIES BUTTON
	addButton({ sdlutils().width() / 2.0f, (sdlutils().height() / 2.0f) - 75 },
		{ 350, 110 },
		gameTextures::upgrade, gameTextures::upgrade_hover, ButtonTypes::upgrade_nexus);

	// PLAY BUTTON
	addButton({ sdlutils().width() / 2.0f, (sdlutils().height() / 2.0f) + 75},
		{ 350, 110 },
		gameTextures::play, gameTextures::play_hover, ButtonTypes::selector_main);

	// CONFIGURATION BUTTON - CAMBIAR IMAGEN
	addButton({ sdlutils().width() / 2.0f, (sdlutils().height() / 2.0f) + 265},
		{ 200, 200 },
		gameTextures::close, gameTextures::close_hover, ButtonTypes::back_selector);

	// NEXUS UPGRADE BUTTON
	addButton({ 200.0f , sdlutils().height() / 2.0f + 200.0f },
		{ 250.0f, 70.0f },
		gameTextures::upgrade, gameTextures::upgrade_hover, ButtonTypes::upgrade_nexus);

	// 1 TOWER BUTTON
	addButton({ sdlutils().width() - 150.0f , (sdlutils().height() /8.0f) * 1 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_nexus);

	// 1 TOWER IMAGE - CAMBIAR IMAGEN
	addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 1 },
		{ 70.0f, 70.0f },
		0, gameTextures::box, _grp_HUD_BACKGROUND);

	// 2 TOWER BUTTON
	addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 2 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_nexus);

	// 2 TOWER IMAGE - CAMBIAR IMAGEN
	addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 2 },
		{ 70.0f, 70.0f },
		0, gameTextures::box, _grp_HUD_BACKGROUND);

	// 3 TOWER BUTTON
	addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 3 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_nexus);

	// 3 TOWER IMAGE - CAMBIAR IMAGEN
	addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 3 },
		{ 70.0f, 70.0f },
		0, gameTextures::box, _grp_HUD_BACKGROUND);

	// 4 TOWER BUTTON
	addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 4 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_nexus);

	// 4 TOWER IMAGE - CAMBIAR IMAGEN
	addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 4 },
		{ 70.0f, 70.0f },
		0, gameTextures::box, _grp_HUD_BACKGROUND);

	// 5 TOWER BUTTON
	addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 5 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_nexus);

	// 5 TOWER IMAGE - CAMBIAR IMAGEN
	addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 5 },
		{ 70.0f, 70.0f },
		0, gameTextures::box, _grp_HUD_BACKGROUND);

	// 6 TOWER BUTTON
	addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 6 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_nexus);

	// 6 TOWER IMAGE - CAMBIAR IMAGEN
	addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 6 },
		{ 70.0f, 70.0f },
		0, gameTextures::box, _grp_HUD_BACKGROUND);

	// 7 TOWER BUTTON
	addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 7 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_nexus);

	// 7 TOWER IMAGE - CAMBIAR IMAGEN
	addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 7 },
		{ 70.0f, 70.0f },
		0, gameTextures::box, _grp_HUD_BACKGROUND);
}

void MainMenuSystem::receive(const Message& m) {
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
	case selector_main:
		loadLevelSelector();
		pause();
		break;
	case upgrade_nexus:
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

void MainMenuSystem::upgradeNexus(){
	Message m;
	// id = upgradeTower
	// mngr_->send(m);
}

void MainMenuSystem::addButton(const Vector2D& pos, const Vector2D& scale, gameTextures tex, gameTextures hov, ButtonTypes type) {
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

void MainMenuSystem::addImage(const Vector2D& pos, const Vector2D& scale, const double rot, gameTextures t, grpId_type grpId) {
	Entity* img = mngr_->addEntity(grpId);
	Transform* tr = mngr_->addComponent<Transform>(img); 
	tr->setScale(scale); 
	Vector2D aux = tr->getScale(); 
	tr->setPosition(pos - aux / 2); 
	tr->setRotation(rot);
	mngr_->addComponent<RenderComponent>(img, t);
}

void MainMenuSystem::pause() {
	for (auto but : mngr_->getHandler(_hdlr_BUTTON)) {
		mngr_->getComponent<ButtonComponent>(but)->setActive(false);
	}
}

