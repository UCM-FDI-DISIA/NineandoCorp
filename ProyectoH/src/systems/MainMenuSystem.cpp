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

	Vector2D towerImagesSize{ 70.5f, 100.0f };

	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();

	

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

#pragma region TOWER BUTTONS
	float but_separation = 175.0f;
	float twr_img_separation = 325.0f;
	float info_separation = 45.0f;
	Vector2D info_size = { 35.0f, 35.0f };

	// 1 TOWER BUTTON - BULLET
	bS->addButton({ sdlutils().width() - but_separation , (sdlutils().height() /8.0f) * 1 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_bullet_main);


	// 1 TOWER BULLET IMAGE
	bS->addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 1 },
		{ towerImagesSize },
		0, gameTextures::bullet_tower_image, _grp_HUD_BACKGROUND);
	// 1 INFO IMAGE
	Message m1;
	m1.id = _m_SHOW_TOWER_INFO;
	m1.show_info.tId = twrId::_twr_BULLET;

	bS->addButton({sdlutils().width() - info_separation, (sdlutils().height() / 8.0f) * 1 }, 
		info_size, 
		gameTextures::info_icon, gameTextures::info_icon, ButtonTypes::show_info, 
		0 ,0 ,0, m1);

	// 2 TOWER BUTTON - CRISTAL
	if (game().getSaveGame()->getTurretsLevels()[_twr_CRISTAL] == 0) {
		bS->addButton({ sdlutils().width() - but_separation , (sdlutils().height() / 8.0f) * 2 },
			{ 200.0f, 70.0f },
			buy, buy_hover, ButtonTypes::upgrade_crystal_main);
	}
	else {
		bS->addButton({ sdlutils().width() - but_separation , (sdlutils().height() / 8.0f) * 2 },
			{ 200.0f, 70.0f },
			upgrade, upgrade_hover, ButtonTypes::upgrade_crystal_main);
	}
	
	// 2 TOWER CRISTAL IMAGE
	bS->addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 2 },
		{ towerImagesSize },
		0, gameTextures::crystal_tower_image, _grp_HUD_BACKGROUND);

	// 3 TOWER BUTTON - SLIME
	if (game().getSaveGame()->getTurretsLevels()[_twr_SLIME] == 0) {
		bS->addButton({ sdlutils().width() - but_separation , (sdlutils().height() / 8.0f) * 3 },
			{ 200.0f, 70.0f },
			buy, buy_hover, ButtonTypes::upgrade_slime_main);
	}
	else {
		bS->addButton({ sdlutils().width() - but_separation , (sdlutils().height() / 8.0f) * 3 },
			{ 200.0f, 70.0f },
			upgrade, upgrade_hover, ButtonTypes::upgrade_slime_main);
	}

	
	// 3 TOWER SLIME IMAGE
	bS->addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 3 },
		{ towerImagesSize },
		0, gameTextures::slime_tower_image, _grp_HUD_BACKGROUND);

	// 4 TOWER BUTTON - SNIPER
	if (game().getSaveGame()->getTurretsLevels()[_twr_DIEGO] == 0) {
		bS->addButton({ sdlutils().width() - but_separation , (sdlutils().height() / 8.0f) * 4 },
			{ 200.0f, 70.0f },
			buy, buy_hover, ButtonTypes::upgrade_sniper_main);
	}
	else {
		bS->addButton({ sdlutils().width() - but_separation , (sdlutils().height() / 8.0f) * 4 },
			{ 200.0f, 70.0f },
			upgrade, upgrade_hover, ButtonTypes::upgrade_sniper_main);
	}

	
	// 4 TOWER SNIPER IMAGE
	bS->addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 4 },
		{ towerImagesSize },
		0, gameTextures::sniper_tower_image, _grp_HUD_BACKGROUND);

	// 5 TOWER BUTTON - FENIX
	if (game().getSaveGame()->getTurretsLevels()[_twr_FENIX] == 0) {
		bS->addButton({ sdlutils().width() - but_separation , (sdlutils().height() / 8.0f) * 5 },
			{ 200.0f, 70.0f },
			buy, buy_hover, ButtonTypes::upgrade_fenix_main);
	}
	else {
		bS->addButton({ sdlutils().width() - but_separation , (sdlutils().height() / 8.0f) * 5 },
			{ 200.0f, 70.0f },
			upgrade, upgrade_hover, ButtonTypes::upgrade_fenix_main);
	}

	
	// 5 TOWER FENIX IMAGE
	bS->addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 5 },
		{ towerImagesSize },
		0, gameTextures::phoenix_tower_image, _grp_HUD_BACKGROUND);

	// 6 TOWER BUTTON - DIRT
	
	bS->addButton({ sdlutils().width() - but_separation , (sdlutils().height() / 8.0f) * 6 },
		{ 200.0f, 70.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_clay_main);
	

	// 6 TOWER DIRT IMAGE
	bS->addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 6 },
		{ towerImagesSize },
		0, gameTextures::clay_tower_image, _grp_HUD_BACKGROUND);

	// 7 TOWER BUTTON - ENHANCER
	if (game().getSaveGame()->getTurretsLevels()[_twr_POWER] == 0) {
		bS->addButton({ sdlutils().width() - but_separation , (sdlutils().height() / 8.0f) * 7 },
			{ 200.0f, 70.0f },
			buy, buy_hover, ButtonTypes::upgrade_enhancer_main);
	}
	else {
		bS->addButton({ sdlutils().width() - but_separation , (sdlutils().height() / 8.0f) * 7 },
			{ 200.0f, 70.0f },
			upgrade, upgrade_hover, ButtonTypes::upgrade_enhancer_main);
	}

	
	// 7 TOWER POWER IMAGE
	bS->addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 7 },
		{ towerImagesSize },
		0, gameTextures::power_tower_image, _grp_HUD_BACKGROUND);

#pragma endregion

	// NEXUS LEVEL TEXT
	addText({ 50.0f, (sdlutils().height() / 2.0f) + 50.0f },
		{ 300.0f, 75.0f }, 0.0f, _grp_HUD_BACKGROUND);
}

void MainMenuSystem::receive(const Message& m) {
	switch (m.id)
	{
	case _m_START_MENU:
		turrentLevels = game().getSaveGame()->getTurretsLevels();
		createNexusImage();
		break;
	case _m_UPDATE_MENU:
		turrentLevels = game().getSaveGame()->getTurretsLevels();
		updateNexusImage();
	}
}

void MainMenuSystem::update() {
}

void MainMenuSystem::createNexusImage()
{
	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();
	// NEXUS LEVEL TEXT
	Vector2D pAux = Vector2D{ 207,600 };
	Vector2D sAux = Vector2D{ 300,100 };
	SDL_Color NombreColor = { 255, 255, 255, 255 };
	string lvl = std::to_string(turrentLevels[twrId::_twr_NEXUS]);
	nexusLvl = bS->addText("Nexus Level: " + lvl, NombreColor, pAux, sAux);

	//Nexus life image
	pAux = Vector2D{ 207,500 };
	sAux = Vector2D{ 300,100 };
	bS->addImage(pAux,sAux,0, gameTextures::life,_grp_HUD_BACKGROUND);
	bS->addImage(pAux, sAux, 0, gameTextures::life_background, _grp_HUD_BACKGROUND);

	nexusImage = mngr_->addEntity(_grp_HUD_FOREGROUND);
	Transform* tr = mngr_->addComponent<Transform>(nexusImage);
	tr->setPosition({ 200,  (sdlutils().height() / 2.0f) - 220.0f });
	Vector2D pos = tr->getPosition();
	mngr_->addComponent<RenderComponent>(nexusImage, gameTextures::nexusLvl); 
	tr->setScale({ 350.0f, 350.0f });
	Vector2D aux = tr->getScale();
	tr->setPosition(pos - aux / 2);
	//FramedImage(int frameColumns = 1, int frameRows = 1, int frameWidth = 0, int frameHeight = 0, int currentFrame = 0, int frameRate = 0, int lastFrame = 1) : 
	mngr_->addComponent<FramedImage>(nexusImage, 4, 1, 2048, 2048, turrentLevels[_twr_NEXUS] - 1, 0, 1);
}

void MainMenuSystem::updateNexusImage() {
	mngr_->getComponent<FramedImage>(nexusImage)->setCurrentFrame(turrentLevels[_twr_NEXUS] - 1);
	string lvl = std::to_string(turrentLevels[twrId::_twr_NEXUS]);
	mngr_->getComponent<TextComponent>(nexusLvl)->changeText("Nexus Level: " + lvl);
}

void MainMenuSystem::addText(const Vector2D& pos, const Vector2D& scale, const double rot, grpId_type grpId) {
	
	Entity* textEntity = mngr_->addEntity(grpId);

	Transform* textTransform = mngr_->addComponent<Transform>(textEntity);
	textTransform->setPosition(pos);
	textTransform->setScale(scale);
	textTransform->setRotation(rot);

	mngr_->addComponent<RenderComponent>(textEntity, nexus_level_text);
}

