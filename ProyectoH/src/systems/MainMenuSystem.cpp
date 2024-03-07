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

	Vector2D towerImagesSize{ 62.5f, 100.0f };

	// NEXUS LEVEL TEXT
	addText({ 50.0f, (sdlutils().height() / 2.0f) + 50.0f}, 
		{ 300.0f, 75.0f}, 0.0f, _grp_GENERAL);

	// BACKGROUND
	addImage({ sdlutils().width() / 2.0f, (sdlutils().height() / 2.0f) },
		{ 2400 , 1800 }, 
		0.0, gameTextures::box, _grp_HUD_BACKGROUND);

	// LOGO
	addImage({ sdlutils().width() / 2.0f, (sdlutils().height() / 2.0f)  - 250},
		{ 266.25f , 198.75f },
		0.0, gameTextures::logo, _grp_HUD_BACKGROUND);	

	// LEFT COLUMN
	addImage({ 200,  sdlutils().height() / 2.0f }, 
		{ sdlutils().height() - 0.0f , 400 },
		90.0, gameTextures::box, _grp_HUD_BACKGROUND);

	// RIGHT COLUMN
	addImage({ sdlutils().width() - 200.0f,  sdlutils().height() / 2.0f },
		{ sdlutils().height() - 0.0f , 400 },
		90.0, gameTextures::box, _grp_HUD_BACKGROUND);

	
	// NEXUS IMAGE - CAMBIAR IMAGEN
	addImage({ 200,  (sdlutils().height() / 2.0f) - 150.0f },
		{ 200 , 200 },
		0.0, gameTextures::nexus_level_3_image, _grp_HUD_BACKGROUND);

	//-------------------------------------------//

	// ENEMIES BUTTON
	addButton({ sdlutils().width() / 2.0f, (sdlutils().height() / 2.0f) - 75 },
		{ 350, 110 },
		gameTextures::enemies_button, gameTextures::enemies_button_hover, ButtonTypes::enemies_main);

	// PLAY BUTTON
	addButton({ sdlutils().width() / 2.0f, (sdlutils().height() / 2.0f) + 75},
		{ 350, 110 },
		gameTextures::play, gameTextures::play_hover, ButtonTypes::selector_main);

	// CONFIGURATION BUTTON
	addButton({ sdlutils().width() / 2.0f, (sdlutils().height() / 2.0f) + 265},
		{ 200, 200 },
		gameTextures::close, gameTextures::close_hover, ButtonTypes::back_selector);

	// NEXUS UPGRADE BUTTON
	addButton({ 200.0f , sdlutils().height() / 2.0f + 200.0f },
		{ 250.0f, 87.5f },
		gameTextures::upgrade, gameTextures::upgrade_hover, ButtonTypes::upgrade_nexus);

	// 1 TOWER BUTTON - BULLET
	addButton({ sdlutils().width() - 150.0f , (sdlutils().height() /8.0f) * 1 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::bullet_menu);

	// 1 TOWER BULLET IMAGE
	addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 1 },
		{ towerImagesSize },
		0, gameTextures::bullet_tower_image, _grp_HUD_BACKGROUND);

	// 2 TOWER BUTTON - CRISTAL
	addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 2 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::glass_menu);

	// 2 TOWER CRISTAL IMAGE
	addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 2 },
		{ towerImagesSize },
		0, gameTextures::crystal_tower_image, _grp_HUD_BACKGROUND);

	// 3 TOWER BUTTON - SLIME
	addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 3 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::slime_menu);

	// 3 TOWER SLIME IMAGE
	addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 3 },
		{ towerImagesSize },
		0, gameTextures::slime_tower_image, _grp_HUD_BACKGROUND);

	// 4 TOWER BUTTON - SNIPER
	addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 4 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::sniper_menu);

	// 4 TOWER SNIPER IMAGE
	addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 4 },
		{ towerImagesSize },
		0, gameTextures::sniper_tower_image, _grp_HUD_BACKGROUND);

	// 5 TOWER BUTTON - FENIX
	addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 5 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::fenix_menu);

	// 5 TOWER FENIX IMAGE
	addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 5 },
		{ towerImagesSize },
		0, gameTextures::phoenix_tower_image, _grp_HUD_BACKGROUND);

	// 6 TOWER BUTTON - DIRT
	addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 6 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::clay_menu);

	// 6 TOWER DIRT IMAGE
	addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 6 },
		{ towerImagesSize },
		0, gameTextures::clay_tower_image, _grp_HUD_BACKGROUND);

	// 7 TOWER BUTTON - ENHANCER
	addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 7 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::enhancer_menu);

	// 7 TOWER POWER IMAGE
	addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 7 },
		{ towerImagesSize },
		0, gameTextures::power_tower_image, _grp_HUD_BACKGROUND);
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

void MainMenuSystem::addText(const Vector2D& pos, const Vector2D& scale, const double rot, grpId_type grpId) {
	
	Entity* textEntity = mngr_->addEntity(grpId);

	Transform* textTransform = mngr_->addComponent<Transform>(textEntity);
	textTransform->setPosition(pos);
	textTransform->setScale(scale);
	textTransform->setRotation(rot);

	Message m;
	m.id = _m_TEXT_MESSAGE;
	m.text_message.ent = textEntity;
	m.text_message.text = stateText::nexus_level;
	mngr_->send(m, true);
	// Añadir Texto
}


void MainMenuSystem::pause() {
	for (auto but : mngr_->getHandler(_hdlr_BUTTON)) {
		mngr_->getComponent<ButtonComponent>(but)->setActive(false);
	}
}

