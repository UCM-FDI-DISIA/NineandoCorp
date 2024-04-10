#include "HUDSystem.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"

HUDSystem::HUDSystem() :
	buttonsSpace_length_() , // 
	infoSpace_length_()
{
	mActive = true;
}
HUDSystem::~HUDSystem(){
}

void HUDSystem::initSystem() {
	twrSel_.imgs.resize(twrId::_twr_SIZE - 1);
	twrSel_.buttons.resize(twrId::_twr_SIZE - 1);
	initial_pos.resize(twrId::_twr_SIZE - 1);

	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();

	buttonsSpace_length_ = sdlutils().width() - 200; 
	float heightH = (float)sdlutils().height() - 80.0f;
	float xAux = (float)(buttonsSpace_length_ - 150 ) / 7;
	float separation = 150.0f;
	Vector2D bSize = Vector2D(100.0f, 100.0f);

	/**
	* 
	*	/ -- BACKGROUND -- /
	* 
	*/
	twrSel_.background = bS->addImage({ (float)sdlutils().width() / 2 , heightH },
		{ (float)sdlutils().width() + 30.0f, 200.0f },

		0.0,
		gameTextures::box,
		_grp_HUD_BACKGROUND);

	/**
	*
	*	/ -- ICONS & BUTTONS -- /
	*
	*/
	#pragma region BULLET TOWER
		twrSel_.buttons[_twr_BULLET] = bS->addButton({ xAux, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::bullet_drag);

		twrSel_.imgs[_twr_BULLET] = bS->addImage(
			{ xAux + 3, heightH },
			{ floatAt("IconBulletScaleX"), floatAt("IconBulletScaleY")},
			0.0f,
			gameTextures::bulletTowerTexture,
			_grp_HUD_FOREGROUND);
		auto dndBullet = mngr_->addComponent<DragAndDrop>(twrSel_.imgs[_twr_BULLET], _twr_BULLET, sdlutils().intConst().at("BalasPrecio"), Height::LOW);
		
		mngr_->addComponent<FramedImage>(twrSel_.imgs[_twr_BULLET],
			intAt("BalasColumns"), intAt("BalasRows"),
			intAt("BalasWidth"), intAt("BalasHeight"),
			0, 0);
		initial_pos[_twr_BULLET] = { xAux + 3, heightH };

	#pragma endregion

	#pragma region CRISTAL TOWER
		twrSel_.buttons[_twr_CRISTAL] = bS->addButton({ xAux * 2, heightH},
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::crystal_drag);
		twrSel_.imgs[_twr_CRISTAL] = bS->addImage(
			{ xAux * 2 + 3, heightH - 10 },
			{ floatAt("IconCristalScaleX"), floatAt("IconCristalScaleY") },
			0.0,
			cristalTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(twrSel_.imgs[_twr_CRISTAL], _twr_CRISTAL, sdlutils().intConst().at("CristalPrecio"), Height::HIGH);
		mngr_->addComponent<FramedImage>(twrSel_.imgs[_twr_CRISTAL],
			intAt("CristalColumns"), intAt("CristalRows"),
			intAt("CristalWidth"), intAt("CristalHeight"),
			0, 0);
		initial_pos[_twr_CRISTAL] = { xAux * 2 + 3, heightH - 10 };

	#pragma endregion

	#pragma region PHOENIX TOWER

		twrSel_.buttons[_twr_FENIX] = bS->addButton({ xAux * 3, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::fenix_drag);

		twrSel_.imgs[_twr_FENIX] = bS->addImage(
			{ xAux * 3 + 3, heightH },
			{ floatAt("IconFenixScaleX"), floatAt("IconFenixScaleY") },
			0.0,
			phoenixTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(twrSel_.imgs[_twr_FENIX], _twr_FENIX, sdlutils().intConst().at("FenixPrecio"), Height::BOTH);
		mngr_->addComponent<FramedImage>(twrSel_.imgs[_twr_FENIX],
			intAt("FenixColumns"), intAt("FenixRows"),
			intAt("FenixWidth"), intAt("FenixHeight"),
			0, 0);

		initial_pos[_twr_FENIX] = { xAux * 3 + 3, heightH };
	#pragma endregion

	#pragma region CLAY TOWER

		twrSel_.buttons[_twr_CLAY] = bS->addButton({ xAux * 4, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::clay_drag);
		twrSel_.imgs[_twr_CLAY] = bS->addImage(
			{ xAux * 4 + 3, heightH },
			{ floatAt("IconClayScaleX"), floatAt("IconClayScaleY") },
			0.0,
			clayTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(twrSel_.imgs[_twr_CLAY], _twr_CLAY, sdlutils().intConst().at("ArcillaPrecio"), Height::PATH);
		mngr_->addComponent<FramedImage>(twrSel_.imgs[_twr_CLAY],
			intAt("ArcillaColumns"), intAt("ArcillaRows"),
			intAt("ArcillaWidth"), intAt("ArcillaHeight"),
			0, 0);

		initial_pos[_twr_CLAY] = { xAux * 4 + 3, heightH };
	#pragma endregion

	#pragma region SNIPER TOWER

		twrSel_.buttons[_twr_DIEGO] = bS->addButton({ xAux * 5, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::sniper_drag);

		twrSel_.imgs[_twr_DIEGO] = bS->addImage(
			{ xAux * 5 + 3, heightH },
			{ floatAt("IconSniperScaleX"), floatAt("IconSniperScaleY") },
			0.0,
			sniperTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(twrSel_.imgs[_twr_DIEGO], _twr_DIEGO, sdlutils().intConst().at("DiegoSniperPrecio"), Height::HIGH);
		mngr_->addComponent<FramedImage>(twrSel_.imgs[_twr_DIEGO],
			intAt("DiegoSniperColumns"), intAt("DiegoSniperRows"),
			intAt("DiegoSniperWidth"), intAt("DiegoSniperHeight"),
			0, 0);

		initial_pos[_twr_DIEGO] = { xAux * 5 + 3, heightH };
	#pragma endregion
	
	#pragma region SLIME TOWER

		twrSel_.buttons[_twr_SLIME] = bS->addButton({ xAux * 6, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::slime_drag);

		twrSel_.imgs[_twr_SLIME] = bS->addImage(
			{ xAux * 6 + 3, heightH },
			{ floatAt("IconSlimeScaleX"), floatAt("IconSlimeScaleY") },
			0.0,
			slimeTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(twrSel_.imgs[_twr_SLIME], _twr_SLIME, sdlutils().intConst().at("SlimePrecio"), Height::LOW);
		mngr_->addComponent<FramedImage>(twrSel_.imgs[_twr_SLIME],
			intAt("SlimeColumns"), intAt("SlimeRows"),
			intAt("SlimeWidth"), intAt("SlimeHeight"),
			0, 0);

		initial_pos[_twr_SLIME] = { xAux * 6 + 3, heightH };
	#pragma endregion

	#pragma region POWER TOWER

		twrSel_.buttons[_twr_POWER] = bS->addButton({ xAux * 7, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::enhancer_drag);

		twrSel_.imgs[_twr_POWER] = bS->addImage(
			{ xAux * 7 + 3, heightH - 4},
			{ floatAt("IconPotenciadorScaleX"), floatAt("IconPotenciadorScaleY") },
			0.0,
			boosterTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(twrSel_.imgs[_twr_POWER], _twr_POWER, sdlutils().intConst().at("PotenciadoraPrecio"), Height::BOTH);
		mngr_->addComponent<FramedImage>(twrSel_.imgs[_twr_POWER],
			intAt("PotenciadoraColumns"), intAt("PotenciadoraRows"),
			intAt("PotenciadoraWidth"), intAt("PotenciadoraHeight"),
			0, 0);

		initial_pos[_twr_POWER] = { xAux * 7 + 3 , heightH - 4 };
	#pragma endregion

	/**
	*
	*	/ -- PAUSE BUTTON -- /
	*
	*/
	bS->addButton({ (float)sdlutils().width() - 50.0f , 50.0f },
		{50.0f, 50.0f},
		gameTextures::pause_button, gameTextures::pause_button_hover,
		ButtonTypes::pause_main);

	
	Vector2D pAux = { xAux * 8.6f, heightH };
	Vector2D sAux = { 250, 90 };
	
	/**
	*
	*	/ -- START ROUND BUTTON -- /
	*
	*/
	twrSel_.roundButton = bS->addButton(pAux, sAux, gameTextures::play, gameTextures::play_hover, ButtonTypes::play_wave);

}

void HUDSystem::receive(const Message& m) {
	switch (m.id) 
	{
	case _m_DRAG:
		dragTowerIcon(twrSel_.imgs[m.drag_data.towerId]);
		break;
	case _m_STOP_DRAG:
		showSelector(true);
		enableAllButtons(true);
		break;
	case _m_PAUSE:
		mActive = !mActive;
		break;
	case _m_OFFSET_CONTEXT:
		cameraOffset_ = m.offset_context.offset;
		break;
	case _m_WAVE_START:
		canStartWave = m.start_wave.play;
		mngr_->getComponent<RenderComponent>(twrSel_.roundButton)->setTexture(mngr_->getComponent<ButtonComponent>(twrSel_.roundButton)->getTexture());
		break;
	case _m_SHOW_UPGRADE_TOWER_MENU:
		if (isOnSelector(m.show_upgrade_twr_menu_data.pos + Vector2D(0, 30))) {
			showUpgradeMenu(m.show_upgrade_twr_menu_data.twr, m.show_upgrade_twr_menu_data.pos);
			showSelector(false);
		}
		break;
	case _m_UPGRADE_TWR_INGAME: 
		if (mngr_->getComponent<UpgradeTowerComponent>(m.upgrade_twr_ingame_data.upCmp)->isMaxLeveled()) {
			mngr_->getComponent<TextComponent>(upM_.lvlText)->changeText("MAX.");
			mngr_->getComponent<Transform>(upM_.lvlText)->getScale()->setX(60.0f);
		}
		else {
			mngr_->getComponent<TextComponent>(upM_.lvlText)->changeText(std::to_string(mngr_->getComponent<UpgradeTowerComponent>(m.upgrade_twr_ingame_data.upCmp)->getLevel()));
		}
		
		break;
	case _m_EXIT_UP_MENU:
		exitUpgradeMenu();
		showSelector(true);
		break;
	}
}	



void HUDSystem::update() {
	if (mActive) {
		auto bC = mngr_->getComponent<ButtonComponent>(twrSel_.roundButton);
		if (canStartWave) {
			bC->setActive(false);
		}
		else {
			bC->setActive(true);
		}
		int i = 0;
		for (auto en : twrSel_.imgs) {
			auto dC = mngr_->getComponent<DragAndDrop>(en);
			if (dC != nullptr && dC->isDragged()) {
				Vector2D mPos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };
				Cell* cell = getCellFromTile(mPos);
				dC->drag(cell->position);

				dC->enableDrop(cell);
				if (ih().mouseButtonEvent()) {
					// click derecho para reset 
					if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::RIGHT) == 1) {
						auto tr = mngr_->getComponent<Transform>(en);
						mngr_->changeEntityId(_grp_HUD_FOREGROUND, en);
						tr->setScale(resetScale(dC->getTowerId()));
						Vector2D aux = tr->getScale();
						tr->setPosition(initial_pos[i] - aux / 2);
						dC->enableDrag(false);
						Message m;
						m.id = _m_STOP_DRAG;
						mngr_->send(m, true);
					}
					//click izquierdo para colocar la torre
					else if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1) {
						auto tr = mngr_->getComponent<Transform>(en);
						if (cell->isFree) {
							dC->drop(tr->getPosition(), Height::LOW);
							cell->isFree = false;
						}
						else {
							//mensaje de no colocar
							Message m;
							m.id = _m_ADD_TEXT;
							m.add_text_data.txt = "NO SE PUEDE COLOCAR EN ESTA POSICION";
							m.add_text_data.color = { 255, 0 ,0, 255 };
							Vector2D txtScale = Vector2D(800.0f, 75.0f);
							m.add_text_data.pos = Vector2D(sdlutils().width() / 2, sdlutils().height() / 2) - (txtScale / 2);
							m.add_text_data.scale = txtScale;
							m.add_text_data.time = 1000;
							mngr_->send(m);
						}
						//resetea el icono de la torre
						dC->enableDrag(false);
						mngr_->changeEntityId(_grp_HUD_FOREGROUND, en);
						tr->setScale(resetScale(dC->getTowerId()));
						Vector2D aux = tr->getScale();
						tr->setPosition(initial_pos[i] - aux / 2);
						Message m;
						m.id = _m_STOP_DRAG;
						mngr_->send(m, true);
					}

				}
			}
			i++;
		}
	}
}

void HUDSystem::showUpgradeMenu(Entity* twr, const Vector2D& pos) {
	auto bS = mngr_->getSystem<ButtonSystem>();
	upM_ = UpgradeMenu();
	auto upCmp = mngr_->getComponent<UpgradeTowerComponent>(twr);

	Vector2D offset = Vector2D(0, 0);
	/** 
	*	/ --- BACKGROUND DE MENU --- / 
	* 
	*	Ajuste del menu con los limites de la camara y HUD
	* 
	*/
	Vector2D posA = { pos.getX() + 300 + 20 + cameraOffset_->x , pos.getY() + cameraOffset_->y };
	if (posA.getX() + 200  > sdlutils().width()) {
	
		offset.setX(-520);
	}
	if (posA.getY() - 150.0f < 0) {
		offset.setY(- (posA.getY() - 150));
		std::cout << std::endl << "DIF Y: " << offset.getY() << std::endl;
	}
	
	upM_.background = bS->addImage(posA + offset,
		{ 400.0f, 300.0f },
		0.0,
		gameTextures::box,
		_grp_HUD_BACKGROUND);
	/**
	*	BOTON DE MEJORA
	*/
	Message m;
	m.id = _m_UPGRADE_TWR_INGAME;
	m.upgrade_twr_ingame_data.upCmp = twr;
	Vector2D posB = { pos.getX() + 390 + cameraOffset_->x, pos.getY() + 85 + cameraOffset_->y };
	upM_.upgradeButton = bS->addButton(posB + offset, 
		{ 150.0f, 60.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_tower, 0,
		m
		);
	/**
	*	TEXTO DE NIVEL
	*/
	SDL_Color c1 = { 255, 255,255,255 };
	Vector2D lvlPos1 = { pos.getX() + 150 + cameraOffset_->x , pos.getY() + 70 + cameraOffset_->y};
	Vector2D lvlScale1 = { 60.0f, 35.0f };
	upM_.twrLvl = bS->addText("LVL: ", c1, lvlPos1 + offset, lvlScale1);

	/**
	*	TEXTO DE NUMERO
	*/
	SDL_Color c2 = { 220, 220, 220, 255 };
	Vector2D lvlPos2 = { pos.getX() + 220 + cameraOffset_->x , pos.getY() + 70 + cameraOffset_->y };
	Vector2D lvlScale2;

		//Comprobacion de nivel para nivel maximo
	std::string lvltxt;
	if (upCmp->isMaxLeveled()) { 
		lvlScale2 = { 60.0f, 35.0f };
		lvltxt = "MAX."; 
	}
	else {
		lvlScale2 = { 20.0f, 35.0f };
		lvltxt = std::to_string(upCmp->getLevel());
	}

	upM_.lvlText = bS->addText(lvltxt, c1, lvlPos2 + offset, lvlScale2);

	/**
	*	BOTON DE SALIR
	*/
	Vector2D posC = { pos.getX() + 460.0f + cameraOffset_->x, pos.getY() - 105.0f + cameraOffset_->y };
	upM_.exitButton = bS->addButton(posC + offset,
		{ 40.0f , 40.0f },
		gameTextures::close, gameTextures::close_hover, ButtonTypes::exit_up_menu);
}

void HUDSystem::exitUpgradeMenu() {
	auto hId = mngr_->getSystem<ButtonSystem>()->hdlr_but_id;

	mngr_->setAlive(upM_.background, false);
	mngr_->setAlive(upM_.upgradeButton, false);
	mngr_->setAlive(upM_.twrDescription, false);
	mngr_->setAlive(upM_.twrLvl, false);
	mngr_->setAlive(upM_.exitButton, false);
	mngr_->setAlive(upM_.cost, false);
	mngr_->setAlive(upM_.lvlText, false);
	mngr_->refresh();

	mngr_->deleteHandler(hId, upM_.exitButton);
	mngr_->deleteHandler(hId, upM_.upgradeButton);
	mngr_->deleteHandler(hId, upM_.background);

	upM_ = UpgradeMenu();

}

void HUDSystem::showSelector(bool active) {
	// buttons
	for (auto b : twrSel_.buttons) {
		mngr_->getComponent<ButtonComponent>(b)->setActive(active);
		mngr_->getComponent<RenderComponent>(b)->isActive_ = active;
	}
	// images
	for (auto i : twrSel_.imgs) {
		mngr_->getComponent<RenderComponent>(i)->isActive_ = active;
	}

	mngr_->getComponent<ButtonComponent>(twrSel_.roundButton)->setActive(active);
	mngr_->getComponent<RenderComponent>(twrSel_.roundButton)->isActive_ = active;

	mngr_->getComponent<RenderComponent>(twrSel_.background)->isActive_ = active;
}

Cell* HUDSystem::getCellFromTile(const Vector2D& pos) {
	auto mS = mngr_->getSystem<mapSystem>();
	auto net = mS->getMalla();
	return net->searchCell(pos);
}

Vector2D HUDSystem::resetScale(twrId tId)
{
	Vector2D scale;
	switch (tId)
	{
	case _twr_BULLET:
		scale.set(Vector2D(floatAt("IconBulletScaleX"), floatAt("IconBulletScaleY")));
		break;
	case _twr_CRISTAL:
		scale.set(Vector2D(floatAt("IconCristalScaleX"), floatAt("IconCristalScaleY")));
		break;
	case _twr_SLIME:
		scale.set(Vector2D(floatAt("IconSlimeScaleX"), floatAt("IconSlimeScaleY")));
		break;
	case _twr_DIEGO:
		scale.set(Vector2D(floatAt("IconSniperScaleX"), floatAt("IconSniperScaleY")));
		break;
	case _twr_FENIX:
		scale.set(Vector2D(floatAt("IconFenixScaleX"), floatAt("IconFenixScaleY")));
		break;
	case _twr_CLAY:
		scale.set(Vector2D(floatAt("IconClayScaleX"), floatAt("IconClayScaleY")));
		break;
	case _twr_POWER:
		scale.set(Vector2D(floatAt("IconPotenciadorScaleX"), floatAt("IconPotenciadorScaleY")));
		break;
	default:
		break;
	}
	return scale;
}

void HUDSystem::dragTowerIcon(Entity* en){
	enableAllButtons(false);
	showSelector(false);
	mngr_->changeEntityId(_grp_HUD_DRAG_AND_DROP, en);
	mngr_->getComponent<DragAndDrop>(en)->enableDrag(true);
}

void HUDSystem::enableAllButtons(bool b)
{
	Message m;
	m.id = _m_ABLEBUTTONS;
	m.able_buttons_data.buttonId = _grp_HUD_FOREGROUND;
	m.able_buttons_data.isAble = b;
	mngr_->send(m);
}


