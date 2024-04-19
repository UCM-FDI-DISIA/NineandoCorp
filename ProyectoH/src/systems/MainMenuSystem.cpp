#include "MainMenuSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

MainMenuSystem::MainMenuSystem() {
	mActive = true;
}

MainMenuSystem::~MainMenuSystem() {
	
}

void MainMenuSystem::initSystem() {

	// cleon: creais mucho reuido con las variables locales.
	// al menos, redefinid cada una por pseparado (no reutiliceis "pAux")

	Vector2D towerImagesSize{ 62.5f, 100.0f };

	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();

	// NEXUS LEVEL TEXT
	addText({ 60.0f, (sdlutils().height() / 2.0f) + 50.0f}, 
		{ 320.0f, 75.0f}, 0.0f, _grp_GENERAL);


	// BACKGROUND
	bS->addImage({ sdlutils().width() / 2.0f, (sdlutils().height() / 2.0f) },
		{ 2400 , 1800 }, 
		0.0, gameTextures::box, _grp_HUD_BACKGROUND);

	// LOGO
	bS->addImage({ sdlutils().width() / 2.0f, (sdlutils().height() / 2.0f)  - 250},
		{ 266.25f , 198.75f },
		0.0, gameTextures::logo, _grp_HUD_BACKGROUND);	

	// LEFT COLUMN
	bS->addImage({ 200,  sdlutils().height() / 2.0f },
		{ sdlutils().height() -0.0f, 400 },
		90.0, gameTextures::column_box, _grp_HUD_BACKGROUND);

	//MONEDAS H DEL JUGADOR
	bS->addImage({ 250,  125 },
		{ 100, 100 },
		0.0, gameTextures::monedaH, _grp_HUD_BACKGROUND);

	// RIGHT COLUMN
	bS->addImage({ sdlutils().width() - 200.0f,  sdlutils().height() / 2.0f },
		{ sdlutils().height() - 0.0f , 400 },
		90.0, gameTextures::column_box, _grp_HUD_BACKGROUND);

	
	// NEXUS IMAGE - CAMBIAR IMAGEN
	bS->addImage({ 200,  (sdlutils().height() / 2.0f) - 150.0f },
		{ 200 , 200 },
		0.0, gameTextures::nexus_level_3_image, _grp_HUD_BACKGROUND);

	//-------------------------------------------//

	// ENEMIES BUTTON
	bS->addButton({ sdlutils().width() / 2.0f, (sdlutils().height() / 2.0f) - 75 },
		{ sdlutils().width() / 3.5f, sdlutils().height() / 8.0f },
		gameTextures::enemies_button, gameTextures::enemies_button_hover, ButtonTypes::enemies_main);

	// PLAY BUTTON
	bS->addButton({ sdlutils().width() / 2.0f, (sdlutils().height() / 2.0f) + 75},
		{ sdlutils().width() / 4.0f, sdlutils().height() / 8.0f },
		gameTextures::play, gameTextures::play_hover, ButtonTypes::selector_main);

	// CONFIGURATION BUTTON
	bS->addButton({ sdlutils().width() / 2.0f, (sdlutils().height() / 2.0f) + 225},
		{ sdlutils().width() / 3.5f, sdlutils().height() / 8.0f},
		gameTextures::settings, gameTextures::settings_hover, ButtonTypes::config);

	// EXIT BUTTON
	bS->addButton({25.f, 25.f },
		{ 50, 50 },
		gameTextures::close, gameTextures::close_hover, ButtonTypes::exit_button);

	// NEXUS UPGRADE BUTTON
	bS->addButton({ 200.0f , sdlutils().height() / 2.0f + 200.0f },
		{ 250.0f, 87.5f },
		gameTextures::upgrade, gameTextures::upgrade_hover, ButtonTypes::upgrade_nexus);

	// 1 TOWER BUTTON - BULLET
	bS->addButton({ sdlutils().width() - 150.0f , (sdlutils().height() /8.0f) * 1 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_bullet_main);

	// 1 TOWER BULLET IMAGE
	bS->addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 1 },
		{ towerImagesSize },
		0, gameTextures::bullet_tower_image, _grp_HUD_BACKGROUND);

	// 2 TOWER BUTTON - CRISTAL
	bS->addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 2 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_crystal_main);

	// 2 TOWER CRISTAL IMAGE
	bS->addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 2 },
		{ towerImagesSize },
		0, gameTextures::crystal_tower_image, _grp_HUD_BACKGROUND);

	// 3 TOWER BUTTON - SLIME
	bS->addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 3 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_slime_main);

	// 3 TOWER SLIME IMAGE
	bS->addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 3 },
		{ towerImagesSize },
		0, gameTextures::slime_tower_image, _grp_HUD_BACKGROUND);

	// 4 TOWER BUTTON - SNIPER
	bS->addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 4 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_sniper_main);

	// 4 TOWER SNIPER IMAGE
	bS->addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 4 },
		{ towerImagesSize },
		0, gameTextures::sniper_tower_image, _grp_HUD_BACKGROUND);

	// 5 TOWER BUTTON - FENIX
	bS->addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 5 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_fenix_main);

	// 5 TOWER FENIX IMAGE
	bS->addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 5 },
		{ towerImagesSize },
		0, gameTextures::phoenix_tower_image, _grp_HUD_BACKGROUND);

	// 6 TOWER BUTTON - DIRT
	bS->addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 6 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_clay_main);

	// 6 TOWER DIRT IMAGE
	bS->addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 6 },
		{ towerImagesSize },
		0, gameTextures::clay_tower_image, _grp_HUD_BACKGROUND);

	// 7 TOWER BUTTON - ENHANCER
	bS->addButton({ sdlutils().width() - 150.0f , (sdlutils().height() / 8.0f) * 7 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_enhancer_main);

	// 7 TOWER POWER IMAGE
	bS->addImage({ sdlutils().width() - 310.0f , (sdlutils().height() / 8.0f) * 7 },
		{ towerImagesSize },
		0, gameTextures::power_tower_image, _grp_HUD_BACKGROUND);

	// NEXUS LEVEL TEXT
	addText({ 50.0f, (sdlutils().height() / 2.0f) + 50.0f },
		{ 300.0f, 75.0f }, 0.0f, _grp_HUD_BACKGROUND);
}

void MainMenuSystem::receive(const Message& m) {
}

void MainMenuSystem::update() {
}

void MainMenuSystem::addText(const Vector2D& pos, const Vector2D& scale, const double rot, grpId_type grpId) {
	
	Entity* textEntity = mngr_->addEntity(grpId);

	Transform* textTransform = mngr_->addComponent<Transform>(textEntity);
	textTransform->setPosition(pos);
	textTransform->setScale(scale);
	textTransform->setRotation(rot);

	mngr_->addComponent<RenderComponent>(textEntity, nexus_level_text);
}

