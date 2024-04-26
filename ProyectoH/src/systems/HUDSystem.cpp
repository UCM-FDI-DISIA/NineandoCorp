#include "HUDSystem.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"

HUDSystem::HUDSystem() :
	buttonsSpace_length_() , // 
	infoSpace_length_(), //
	upMenuIsOn(false)
{
	mActive = true;
}
HUDSystem::~HUDSystem(){
}

void HUDSystem::initSystem() {
	twrSel_.buttons.resize(twrId::_twr_SIZE - 1);

	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();

	buttonsSpace_length_ = sdlutils().width() - 200; 
	float heightH = (float)sdlutils().height() - 100.0f;
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
	 
	// Color general para el texto
	SDL_Color moneyColor = { 255, 255, 255, 255 };

	#pragma region BULLET TOWER
	TowerButton tb1;
		tb1.button = bS->addButton({ xAux, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::bullet_drag);

		tb1.img = bS->addImage(
			{ xAux * ((int)_twr_BULLET + 1) + 3, heightH },
			{ floatAt("IconBulletScaleX"), floatAt("IconBulletScaleY")},
			0.0f,
			gameTextures::bulletTowerTexture,
			_grp_HUD_FOREGROUND);
		auto dndBullet = mngr_->addComponent<DragAndDrop>(tb1.img , _twr_BULLET, sdlutils().intConst().at("BalasPrecio"), Height::LOW);
		
		mngr_->addComponent<LockComponent>(tb1.img, game().getSaveGame()->getTurretsLevels()[_twr_BULLET] == 0);
		mngr_->addComponent<FramedImage>(tb1.img ,
			intAt("BalasColumns"), intAt("BalasRows"),
			intAt("BalasWidth"), intAt("BalasHeight"),
			0, 0);
		tb1.initialPos = Vector2D( xAux * ((int)_twr_BULLET + 1) + 3, heightH );
		
		tb1.moneyTxt = bS->addText(std::to_string(sdlutils().intConst().at("BalasPrecio")), moneyColor, { xAux * ((int)_twr_BULLET + 1) - 20 , heightH +  67}, {bSize.getX() / 2 , 30});

		//Icono de moneda - TEMPORAL, CAMBIAR MAS TARDE A LA MONEDA INGAME
		tb1.coinImg = bS->addImage(
			{ xAux * ((int)_twr_BULLET + 1) + bSize.getX() / 4, heightH + 67.5f},
			{30.0f, 30.0f },
			0.0f,
			gameTextures::monedaDorada,
			_grp_HUD_FOREGROUND);

		twrSel_.buttons[_twr_BULLET] = tb1;
	#pragma endregion

	#pragma region CLAY TOWER
		TowerButton tb4;
		tb4.button = bS->addButton({ xAux * ((int)_twr_CLAY + 1), heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::clay_drag);
		mngr_->addComponent<LockComponent>(tb4.button, game().getSaveGame()->getTurretsLevels()[_twr_CLAY] == 0);

		tb4.img = bS->addImage(
			{ xAux * ((int)_twr_CLAY + 1) + 3, heightH },
			{ floatAt("IconClayScaleX"), floatAt("IconClayScaleY") },
			0.0,
			clayTowerTexture,
			_grp_HUD_FOREGROUND);
		mngr_->addComponent<LockComponent>(tb1.img, game().getSaveGame()->getTurretsLevels()[_twr_CLAY] == 0);
		mngr_->addComponent<DragAndDrop>(tb4.img, _twr_CLAY, sdlutils().intConst().at("ArcillaPrecio"), Height::PATH);
		mngr_->addComponent<FramedImage>(tb4.img,
			intAt("ArcillaColumns"), intAt("ArcillaRows"),
			intAt("ArcillaWidth"), intAt("ArcillaHeight"),
			0, 0);

		tb4.initialPos = Vector2D( xAux * ((int)_twr_CLAY + 1) + 3, heightH );

		// Set tower price
		tb4.moneyTxt = bS->addText(std::to_string(sdlutils().intConst().at("ArcillaPrecio")), moneyColor, { (xAux * ((int)_twr_CLAY + 1)) - 20, heightH + 67 }, { bSize.getX() / 2 , 30 });

		//Icono de moneda - TEMPORAL, CAMBIAR MAS TARDE A LA MONEDA INGAME
		tb4.coinImg = bS->addImage(
			{ (xAux * ((int)_twr_CLAY + 1)) + bSize.getX() / 4 , heightH + 67.5f },
			{ 30.0f, 30.0f },
			0.0f,
			gameTextures::monedaDorada,
			_grp_HUD_FOREGROUND);

	

		twrSel_.buttons[_twr_CLAY] = tb4;
	#pragma endregion

	#pragma region SLIME TOWER
		TowerButton tb6;
		tb6.button = bS->addButton({ xAux * ((int)_twr_SLIME+ 1), heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::slime_drag);
		mngr_->addComponent<LockComponent>(tb6.button, game().getSaveGame()->getTurretsLevels()[_twr_SLIME] == 0); 

		tb6.img = bS->addImage(
			{ xAux * ((int)_twr_SLIME + 1) + 3, heightH },
			{ floatAt("IconSlimeScaleX"), floatAt("IconSlimeScaleY") },
			0.0,
			slimeTowerTexture,
			_grp_HUD_FOREGROUND);
		
		mngr_->addComponent<LockComponent>(tb6.img, game().getSaveGame()->getTurretsLevels()[_twr_SLIME] == 0); 
		mngr_->addComponent<DragAndDrop>(tb6.img, _twr_SLIME, sdlutils().intConst().at("SlimePrecio"), Height::LOW);
		mngr_->addComponent<FramedImage>(tb6.img,
			intAt("SlimeColumns"), intAt("SlimeRows"),
			intAt("SlimeWidth"), intAt("SlimeHeight"),
			0, 0);

		tb6.initialPos =  Vector2D( xAux * ((int)_twr_SLIME + 1) + 3, heightH );

		if (!game().getSaveGame()->getTurretsLevels()[_twr_SLIME] == 0) {
			tb6.moneyTxt = bS->addText(std::to_string(sdlutils().intConst().at("SlimePrecio")), moneyColor, { (xAux * ((int)_twr_SLIME + 1)) - 20, heightH + 67 }, { bSize.getX() / 2 , 30 });

			//Icono de moneda - TEMPORAL, CAMBIAR MAS TARDE A LA MONEDA INGAME
			tb6.coinImg = bS->addImage(
				{ (xAux * ((int)_twr_SLIME + 1)) + bSize.getX() / 4 , heightH + 67.5f },
				{ 30.0f, 30.0f },
				0.0f,
				gameTextures::monedaDorada,
				_grp_HUD_FOREGROUND);
		}
		// Set tower price

		twrSel_.buttons[_twr_SLIME] = tb6;
	#pragma endregion

	#pragma region PHOENIX TOWER
		TowerButton tb3;
		tb3.button = bS->addButton({ xAux * ((int)_twr_FENIX + 1), heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::fenix_drag);
		mngr_->addComponent<LockComponent>(tb3.button, game().getSaveGame()->getTurretsLevels()[_twr_FENIX] == 0);

		tb3.img = bS->addImage(
			{ xAux * ((int)_twr_FENIX + 1) + 3, heightH },
			{ floatAt("IconFenixScaleX"), floatAt("IconFenixScaleY") },
			0.0,
			phoenixTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<LockComponent>(tb3.img, game().getSaveGame()->getTurretsLevels()[_twr_FENIX] == 0);
		mngr_->addComponent<DragAndDrop>(tb3.img, _twr_FENIX, sdlutils().intConst().at("FenixPrecio"), Height::BOTH);
		mngr_->addComponent<FramedImage>(tb3.img,
			intAt("FenixColumns"), intAt("FenixRows"),
			intAt("FenixWidth"), intAt("FenixHeight"),
			0, 0);

		tb3.initialPos = Vector2D(xAux * ((int)_twr_FENIX + 1) + 3, heightH );
		if (!game().getSaveGame()->getTurretsLevels()[_twr_FENIX] == 0) {

			// Set tower price
			tb3.moneyTxt = bS->addText(std::to_string(sdlutils().intConst().at("FenixPrecio")), moneyColor, { (xAux * ((int)_twr_FENIX + 1)) - 20, heightH + 67 }, { bSize.getX() / 2 , 30 });

			//Icono de moneda - TEMPORAL, CAMBIAR MAS TARDE A LA MONEDA INGAME
			tb3.coinImg = bS->addImage(
				{ (xAux * ((int)_twr_FENIX + 1)) + bSize.getX() / 4 , heightH + 67.5f },
				{ 30.0f, 30.0f },
				0.0f,
				gameTextures::monedaDorada,
				_grp_HUD_FOREGROUND);
		}

		twrSel_.buttons[_twr_FENIX] = tb3;
	#pragma endregion

	#pragma region SNIPER TOWER
		TowerButton tb5;
		tb5.button = bS->addButton({ xAux * ((int)_twr_DIEGO + 1), heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::sniper_drag);
		mngr_->addComponent<LockComponent>(tb5.button, game().getSaveGame()->getTurretsLevels()[_twr_DIEGO] == 0);
		tb5.img = bS->addImage(
			{ xAux * ((int)_twr_DIEGO + 1) + 3, heightH },
			{ floatAt("IconSniperScaleX"), floatAt("IconSniperScaleY") },
			0.0,
			sniperTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<LockComponent>(tb5.img, game().getSaveGame()->getTurretsLevels()[_twr_DIEGO] == 0);
		mngr_->addComponent<DragAndDrop>(tb5.img, _twr_DIEGO, sdlutils().intConst().at("DiegoSniperPrecio"), Height::HIGH);
		mngr_->addComponent<FramedImage>(tb5.img,
			intAt("DiegoSniperColumns"), intAt("DiegoSniperRows"),
			intAt("DiegoSniperWidth"), intAt("DiegoSniperHeight"),
			0, 0);

		tb5.initialPos = Vector2D( xAux * ((int)_twr_DIEGO + 1) + 3, heightH );
		if (!game().getSaveGame()->getTurretsLevels()[_twr_DIEGO] == 0) {

			// Set tower price
			tb5.moneyTxt = bS->addText(std::to_string(sdlutils().intConst().at("DiegoSniperPrecio")), moneyColor, { (xAux * ((int)_twr_DIEGO + 1)) - 20, heightH + 67 }, { bSize.getX() / 2 , 30 });

			//Icono de moneda - TEMPORAL, CAMBIAR MAS TARDE A LA MONEDA INGAME
			tb5.coinImg = bS->addImage(
				{ (xAux * ((int)_twr_DIEGO + 1)) + bSize.getX() / 4 , heightH + 67.5f },
				{ 30.0f, 30.0f },
				0.0f,
				gameTextures::monedaDorada,
				_grp_HUD_FOREGROUND);
		}
		twrSel_.buttons[_twr_DIEGO] = tb5;
	#pragma endregion

	#pragma region POWER TOWER
		TowerButton tb7;
		tb7.button = bS->addButton({ xAux * ((int)_twr_POWER + 1), heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::enhancer_drag);
		mngr_->addComponent<LockComponent>(tb7.button, game().getSaveGame()->getTurretsLevels()[_twr_POWER] == 0);

		tb7.img = bS->addImage(
			{ xAux * ((int)_twr_POWER + 1) + 3, heightH - 4},
			{ floatAt("IconPotenciadorScaleX"), floatAt("IconPotenciadorScaleY") },
			0.0,
			boosterTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<LockComponent>(tb7.img, game().getSaveGame()->getTurretsLevels()[_twr_POWER] == 0);
		mngr_->addComponent<DragAndDrop>(tb7.img, _twr_POWER, sdlutils().intConst().at("PotenciadoraPrecio"), Height::BOTH);
		mngr_->addComponent<FramedImage>(tb7.img,
			intAt("PotenciadoraColumns"), intAt("PotenciadoraRows"),
			intAt("PotenciadoraWidth"), intAt("PotenciadoraHeight"),
			0, 0);

		tb7.initialPos = Vector2D( xAux * ((int)_twr_POWER + 1) + 3, heightH - 4 );

		if (!game().getSaveGame()->getTurretsLevels()[_twr_POWER] == 0) {

			// Set tower price
			tb7.moneyTxt = bS->addText(std::to_string(sdlutils().intConst().at("PotenciadoraPrecio")), moneyColor, { (xAux * ((int)_twr_POWER + 1)) - 20, heightH + 67 }, { bSize.getX() / 2 , 30 });

			//Icono de moneda - TEMPORAL, CAMBIAR MAS TARDE A LA MONEDA INGAME
			tb7.coinImg = bS->addImage(
				{ (xAux * ((int)_twr_POWER + 1)) + bSize.getX() / 4 , heightH + 67.5f },
				{ 30.0f, 30.0f },
				0.0f,
				gameTextures::monedaDorada,
				_grp_HUD_FOREGROUND);
		}

		twrSel_.buttons[_twr_POWER] = tb7;
	#pragma endregion

	#pragma region CRISTAL TOWER
		TowerButton tb2;
		tb2.button = bS->addButton({ xAux * ((int)_twr_CRISTAL + 1), heightH},
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::crystal_drag);
		mngr_->addComponent<LockComponent>(tb2.button, game().getSaveGame()->getTurretsLevels()[_twr_CRISTAL] == 0);

		tb2.img = bS->addImage(
			{ xAux * ((int)_twr_CRISTAL + 1) + 3, heightH - 10 },
			{ floatAt("IconCristalScaleX"), floatAt("IconCristalScaleY") },
			0.0,
			cristalTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<LockComponent>(tb2.img, game().getSaveGame()->getTurretsLevels()[_twr_CRISTAL] == 0);
		mngr_->addComponent<DragAndDrop>(tb2.img, _twr_CRISTAL, sdlutils().intConst().at("CristalPrecio"), Height::HIGH);
		mngr_->addComponent<FramedImage>(tb2.img,
			intAt("CristalColumns"), intAt("CristalRows"),
			intAt("CristalWidth"), intAt("CristalHeight"),
			0, 0);
		tb2.initialPos = Vector2D(xAux * ((int)_twr_CRISTAL + 1) + 3, heightH - 10 );

		if (!game().getSaveGame()->getTurretsLevels()[_twr_CRISTAL] == 0) {

			// Set tower price
			tb2.moneyTxt = bS->addText(std::to_string(sdlutils().intConst().at("CristalPrecio")), moneyColor, { (xAux * ((int)_twr_CRISTAL + 1)) - 20, heightH + 67 }, { bSize.getX() / 2 , 30 });

			//Icono de moneda - TEMPORAL, CAMBIAR MAS TARDE A LA MONEDA INGAME
			tb2.coinImg = bS->addImage(
				{ (xAux * ((int)_twr_CRISTAL + 1)) + bSize.getX() / 4 , heightH + 67.5f },
				{ 30.0f, 30.0f },
				0.0f,
				gameTextures::monedaDorada,
				_grp_HUD_FOREGROUND);
		}

		twrSel_.buttons[_twr_CRISTAL] = tb2;

	#pragma endregion


	//ICONO MONEDAS DEL JUGADOR
	bS->addImage({ 175,  25 },
		{ 60, 60 },
		0.0, gameTextures::monedaDorada, _grp_HUD_BACKGROUND);

	/** 
	*
	*	/ -- PAUSE BUTTON -- /
	*
	*/
	pauseButton = bS->addButton({ (float)sdlutils().width() - 50.0f , 50.0f },
		{50.0f, 50.0f},
		gameTextures::pause_button, gameTextures::pause_button_hover,
		ButtonTypes::pause_main);

	/**
	*
	*	/ -- ACELERATION BUTTON -- /
	*
	*/
	acelerateButton = bS->addButton({ (float)sdlutils().width() - 50.0f , 120.0f },
		{ 50.0f, 50.0f },
		gameTextures::acelerate_x1, gameTextures::acelerate_x1_hover,
		ButtonTypes::acelerate);
	mngr_->setHandler(_hdlr_BUTTON_ACELERATE, acelerateButton);

	Vector2D pAux = { sdlutils().width() - 150.0f, heightH };
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
		dragTowerIcon(twrSel_.buttons[m.drag_data.towerId].img);
		break;
	case _m_STOP_DRAG:
		showSelector(true);
		enableAllButtons(true);
		break;
	case _m_PAUSE:
		mActive = !m.start_pause.onPause;
		break;
	case _m_ACELERATE:
		NewAcelerationButton(m.acelerate_plus.acel);
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
			upMenuIsOn = true;
		}
		break;
	case _m_UPGRADE_TWR_INGAME: 
		if (mngr_->getComponent<UpgradeTowerComponent>(m.upgrade_twr_ingame_data.upCmp)->isMaxLeveled() && mngr_->getComponent<UpgradeTowerComponent>(m.upgrade_twr_ingame_data.upCmp)->getLevel() == 4) {
			mngr_->getComponent<TextComponent>(upM_.lvlText)->changeText("MAX.");
			mngr_->getComponent<Transform>(upM_.lvlText)->getScale()->setX(60.0f);
		}
		else {
			mngr_->getComponent<TextComponent>(upM_.lvlText)->changeText(std::to_string(mngr_->getComponent<UpgradeTowerComponent>(m.upgrade_twr_ingame_data.upCmp)->getLevel()));			
		}
		updateTowerInfo();
		break;
	case _m_EXIT_UP_MENU:
		exitUpgradeMenu();
		showSelector(true);
		upMenuIsOn = false;
		break;
	case _m_HIDE_UPGRADEBUTTON:
		if (upMenuIsOn) {
			mngr_->setAlive(upM_.coinImg, false);
			mngr_->deleteHandler(mngr_->getSystem<ButtonSystem>()->hdlr_but_id, upM_.coinImg);
			mngr_->setAlive(upM_.upgradeButton, false);
			mngr_->deleteHandler(mngr_->getSystem<ButtonSystem>()->hdlr_but_id, upM_.upgradeButton);
			mngr_->setAlive(upM_.upCost, false);
			mngr_->deleteHandler(mngr_->getSystem<ButtonSystem>()->hdlr_but_id, upM_.upCost);
		}
		break;
	case _m_SELL_TOWER:
		Message m;
		m.id = _m_EXIT_UP_MENU;
		mngr_->send(m);
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
		if (upMenuIsOn) {
			if (ih().mouseButtonEvent()) {
				if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1) {
					Vector2D mousePos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };
					if (!isOnUpMenu(mousePos)) {
						Message m;
						m.id = _m_EXIT_UP_MENU;
						mngr_->send(m);
					}
				}
			}
		}
		for (auto tb : twrSel_.buttons) {
			auto en = tb.img;
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
						tr->setPosition(tb.initialPos - aux / 2);
						dC->enableDrag(false);
						Message m;
						m.id = _m_STOP_DRAG;
						mngr_->send(m, true);
					}
					//click izquierdo para colocar la torre
					else if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1) {
						
						auto tr = mngr_->getComponent<Transform>(en);
						if (cell->isFree) {
							dC->drop(tr->getPosition(), Height::LOW, cell);
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
						tr->setPosition(tb.initialPos - aux / 2);
						Message m;
						m.id = _m_STOP_DRAG;
						mngr_->send(m, true);
					}

				}
			}
		}
	}
}

bool HUDSystem::isOnUpMenu(const Vector2D& mPos) const
{
	Vector2D menuScale = mngr_->getComponent<Transform>(upM_.background)->getScale();
	Vector2D menuPos = mngr_->getComponent<Transform>(upM_.background)->getPosition();
	float x = mPos.getX();
	float y = mPos.getY();
	float up = menuPos.getY();
	float down = menuPos.getY() + menuScale.getY();
	float right = menuPos.getX() + menuScale.getX();
	float left = menuPos.getX();

	return  x > left && x < right && y < down && y > up;
}

void HUDSystem::showUpgradeMenu(Entity* twr, const Vector2D& pos) {
	tower_ = twr;

	auto bS = mngr_->getSystem<ButtonSystem>();
	upM_ = UpgradeMenu();
	auto upCmp = mngr_->getComponent<UpgradeTowerComponent>(twr);

	auto hpCmp = mngr_->getComponent<HealthComponent>(twr);

	auto bt = mngr_->getComponent<BulletTower>(twr);
	auto ds = mngr_->getComponent<DiegoSniperTower>(twr);
	auto st = mngr_->getComponent<SlimeTowerComponent>(twr);
	auto ft = mngr_->getComponent<PhoenixTower>(twr);
	auto et = mngr_->getComponent<EnhancerTower>(twr);
	auto dt = mngr_->getComponent<DirtTower>(twr);
	auto ct = mngr_->getComponent<CrystalTower>(twr);

	float range = 100;
	int damage = 0;
	float reloadTime = 0.0;

	if (bt != nullptr) { range = bt->getRange(); damage = bt->getDamage(); reloadTime = bt->getReloadTime(); }
	else if (ds != nullptr) { range = ds->getRange(); damage = ds->getDamage(); reloadTime = ds->getReloadTime(); }
	else if (st != nullptr) { range = st->getRange(); damage = st->getDPS(); reloadTime = st->getReloadTime(); }
	else if (ft != nullptr) { range = ft->getRange(); damage = ft->getDamage(); reloadTime = ft->getCoolingTime(); }
	else if (et != nullptr) { range = et->getRange(); }
	else if (dt != nullptr) { range = dt->getRange(); }
	else if (ct != nullptr) { range = ct->getRange(); reloadTime = ct->getTimeToShield(); }

	Vector2D offset = Vector2D(0, 0);
	/** 
	*   / --- RANGO DE LA TORRE --- / 
	*	/ --- BACKGROUND DE MENU --- / 
	* 
	*	Ajuste del menu con los limites de la camara y HUD
	* 
	*/
	Vector2D posA = { pos.getX() + 300 + 20 + cameraOffset_->x , pos.getY() + cameraOffset_->y };
	if (posA.getX() + 250  > sdlutils().width()) {
	
		offset.setX(-520);
	}
	if (posA.getY() - 150.0f < 0) {
		offset.setY(- (posA.getY() - 150));
		std::cout << std::endl << "DIF Y: " << offset.getY() << std::endl;
	}
	upM_.range = bS->addImage(posA + Vector2D(-255, 105),
		{ range * 2, range * 1.5f },
		0.0,
		gameTextures::rangeCircle,
		_grp_HUD_BACKGROUND);

	//Escala del background
	Vector2D bgScale = { 500.0f, 350.0f };
	upM_.background = bS->addImage(posA + offset,
		bgScale,
		180.0,
		gameTextures::box,
		_grp_HUD_BACKGROUND);
	/**
	*	NOMBRE DE TORRE
	*/
	SDL_Color c1 = { 255, 255,255,255 };
	basic_string tName = getTowerName(upCmp->id_);
	Vector2D namePos = Vector2D(posA.getX() - tName.size() / 2, posA.getY() - (bgScale.getY() / 2) + 60);
	Vector2D nameScale = { 17.0f * tName.size(), 40 };
	upM_.twrName = bS->addText(tName, c1,
		 namePos + offset,
		nameScale
	);

	#pragma region TOWER STATS
	/**
	*	FRAME
	*/
	Vector2D fScale = { bgScale.getX() / 2 , (bgScale.getY() - nameScale.getY() * 2) - 20};
	Vector2D framePos = {(posA.getX() - bgScale.getX() / 4) + 20, posA.getY() + 30};
		
	upM_.frame = bS->addImage(framePos + offset, fScale, 0, gameTextures::white_frame, grpId::_grp_HUD_FOREGROUND);

	//Offset en eje y para los textos en relacion al frame
	float hOffset = (framePos.getY() - (framePos.getY() - fScale.getY() / 2) ) / 3;

	//Coordenada x para que todos los textos esten alineados
	float coord_texts_x = framePos.getX() - fScale.getX() / 2 + 60;

	//tama�o de la fuente
	Vector2D fontSize = { 20.0f, 35.0f };

	/**
	*	TEXTO DE NIVEL
	*/	
	Vector2D lvlScale1 = { 60.0f, 35.0f };
	Vector2D lvlPos1 = { coord_texts_x, framePos.getY() - (2 * hOffset) };
	upM_.twrLvl = bS->addText("LVL: ", c1, lvlPos1 + offset, lvlScale1);
	
	/**
	*	TEXTO DE NUMERO
	*/
	SDL_Color c2 = { 220, 220, 220, 255 };
	Vector2D lvlScale2;
		//Comprobacion de nivel para nivel maximo
	basic_string lvltxt = "";
	if (upCmp->isMaxLeveled() && upCmp->getLevel() == 4) { 
		
		lvltxt = "MAX."; 
	}
	else {
		lvltxt = std::to_string(upCmp->getLevel());
	}
	lvlScale2 = { (float)lvltxt.size() * 20, 35.0f };
	Vector2D lvlPos2 = { lvlPos1.getX()  + lvlScale2.getX() + 30  , lvlPos1.getY()};

	upM_.lvlText = bS->addText(lvltxt, c1, lvlPos2 + offset, lvlScale2);

	/**
	*	TEXTO DE VIDA
	*/
	Vector2D hpScale = { 90.0f, 35.0f };
	Vector2D hpPos = { coord_texts_x + hpScale.getX() / 4 - 7, framePos.getY() - hOffset + 17};
	upM_.hpText = bS->addText("HP: " + to_string((int)hpCmp->getHealth()), c1, hpPos + offset, hpScale);

	/**
	*	TEXTO DE DANO
	*/
	Vector2D dmgScale = { 100.0f, 35.0f };
	Vector2D dmgPos = { coord_texts_x + dmgScale.getX() / 4 - 3, framePos.getY() + hOffset - 17};
	upM_.damageText = bS->addText("DMG: " + to_string((int)damage), c1, dmgPos + offset, dmgScale);

	/**
	*	TEXTO DE RECARGA
	*/
	Vector2D relScale = { 130.0f, 35.0f };
	Vector2D relPos = { coord_texts_x + relScale.getX() / 4 + 7, framePos.getY() + (2 * hOffset)};
	upM_.reloadText = bS->addText("RELOAD: " + to_string((int)reloadTime), c1, relPos + offset, relScale);


#pragma endregion
	if (!upCmp->isMaxLeveled()) {
		/**
	*	BOTON DE MEJORA
	*/
	Message m;
	m.id = _m_UPGRADE_TWR_INGAME;
	m.upgrade_twr_ingame_data.upCmp = twr;
	Vector2D posB = { posA.getX() + bgScale.getX() / 4,pos.getY() + cameraOffset_->y };
	
	Vector2D upButScale = { 150.0f, 60.0f };
	upM_.upgradeButton = bS->addButton(posB + offset, 
		upButScale,
		upgrade, upgrade_hover, ButtonTypes::upgrade_tower, 0,0,0,
		m
		);

	/**
	*	TEXTO COSTE & IMAGEN MONEDA
	*/
	int upCost = upCmp->getUpgradeCost();
	basic_string cost_s = std::to_string(upCost);
	//Escala texto 
	Vector2D scaleUpText = { 20.0f * cost_s.size(), 35.0f };
	//Escala icono moneda
	Vector2D scaleCoin = { 35.0f, 35.0f };

	//Separacion entre el texto y la imagen de la moneda
	float separation = 20.0f;
	//Longitud total de las dos entidades
	float total_length = scaleUpText.getX() + scaleCoin.getX() + separation;
	//Posicion central de ambas entidades
	Vector2D centerPos = { posB.getX(), posB.getY() - upButScale.getY() / 2 - scaleUpText.getY() / 2 - 10};

	//Posicion texto
	Vector2D posUpText = { centerPos.getX() - (total_length / 2) + (scaleUpText.getX() / 2) , centerPos.getY()};
	//Instancia del texto
	upM_.upCost = bS->addText(cost_s, c1, posUpText + offset, scaleUpText);

	//Posicion del icono de la moneda
	Vector2D cpos = { centerPos.getX() + (total_length / 2) - (scaleCoin.getX() / 2) ,centerPos.getY()};
	//Instancia de la imagen de la moneda
	upM_.coinImg = bS->addImage(
		cpos + offset, scaleCoin, 0, gameTextures::monedaDorada,
		grpId::_grp_HUD_FOREGROUND
	);
	}
	

	/**
	*	BOTON DE VENDER
	*/
	Message m1;
	m1.id = _m_SELL_TOWER;
	m1.sell_tower_data.twr = tower_;

	Vector2D posC = { posA.getX() + bgScale.getX() / 4, pos.getY() + 85 + cameraOffset_->y };
	upM_.sellButton = bS->addButton(posC + offset,
		{ 150.0f, 60.0f },
		sell, sell_hover, ButtonTypes::sell_tower, 0,0,0,
		m1
	);
	

	/**
	*	BOTON DE SALIR
	*/
	Vector2D exitScale = { 40.0f, 40.0f };
	Vector2D posD = { posA.getX() + (bgScale.getX() / 2 ) - exitScale.getX(), posA.getY() - bgScale.getY() / 2 + exitScale.getY() + 10};
	upM_.exitButton = bS->addButton(posD + offset,
		{ 40.0f , 40.0f },
		gameTextures::close, gameTextures::close_hover, ButtonTypes::exit_up_menu);
}

void HUDSystem::NewAcelerationButton(float acel) {
	auto hId = mngr_->getHandler(_hdlr_BUTTON_ACELERATE);
	for (Entity* en : hId) {
		mngr_->getComponent<ButtonComponent>(en)->setActive(false);
		mngr_->getComponent<RenderComponent>(en)->isActive = false;
	}
	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();
	gameTextures butText, butText_hover;
	if (acel == 1) {
		butText = acelerate_x1;
		butText_hover = acelerate_x1_hover;
	}
	else if (acel == 1.5) {
		butText = acelerate_x1_5;
		butText_hover = acelerate_x1_5_hover;
	}
	else {
		butText = acelerate_x2;
		butText_hover = acelerate_x2_hover;
	}
	acelerateButton = bS->addButton({ (float)sdlutils().width() - 50.0f , 120.0f },
		{ 50.0f, 50.0f },
		butText, butText_hover,
		ButtonTypes::acelerate);
	mngr_->setHandler(_hdlr_BUTTON_ACELERATE, acelerateButton);
}

void HUDSystem::exitUpgradeMenu() {
	auto hId = mngr_->getSystem<ButtonSystem>()->hdlr_but_id;

	mngr_->setAlive(upM_.background, false);
	mngr_->setAlive(upM_.upgradeButton, false);
	mngr_->setAlive(upM_.twrName, false);
	mngr_->setAlive(upM_.twrLvl, false);
	mngr_->setAlive(upM_.exitButton, false);
	mngr_->setAlive(upM_.cost, false);
	mngr_->setAlive(upM_.lvlText, false);
	mngr_->setAlive(upM_.sellButton, false);
	mngr_->setAlive(upM_.range, false);
	mngr_->setAlive(upM_.hpText, false);
	mngr_->setAlive(upM_.damageText, false);
	mngr_->setAlive(upM_.reloadText, false);
	mngr_->setAlive(upM_.upCost, false);
	mngr_->setAlive(upM_.coinImg, false);
	mngr_->setAlive(upM_.frame, false);
	mngr_->refresh();

	mngr_->deleteHandler(hId, upM_.coinImg);
	mngr_->deleteHandler(hId, upM_.frame);
	mngr_->deleteHandler(hId, upM_.sellButton);
	mngr_->deleteHandler(hId, upM_.exitButton);
	mngr_->deleteHandler(hId, upM_.upgradeButton);
	mngr_->deleteHandler(hId, upM_.background);
	mngr_->deleteHandler(hId, upM_.range);
	mngr_->deleteHandler(hId, upM_.damageText);
	mngr_->deleteHandler(hId, upM_.reloadText);
	mngr_->deleteHandler(hId, upM_.hpText);
	mngr_->deleteHandler(hId, upM_.twrLvl);
	mngr_->deleteHandler(hId, upM_.lvlText);
	mngr_->deleteHandler(hId, upM_.twrName);
	mngr_->deleteHandler(hId, upM_.upCost);

	tower_ = nullptr;

	upM_ = UpgradeMenu();

}

void HUDSystem::showSelector(bool active) {
	// TowerButtons
	for (auto tb : twrSel_.buttons) {
		
		//Boton
		auto b = tb.button;
		if (b != nullptr) {
			mngr_->getComponent<ButtonComponent>(b)->setActive(active);
			mngr_->getComponent<RenderComponent>(b)->isActive = active;
		}
		//Icono torre
		if(tb.img != nullptr)
		mngr_->getComponent<RenderComponent>(tb.img)->isActive = active;
		//Texto de dinero
		if(tb.moneyTxt != nullptr)
			mngr_->getComponent<TextComponent>(tb.moneyTxt)->isActive = active;
		//Icono de dinero
		if(tb.coinImg != nullptr)
			mngr_->getComponent<RenderComponent>(tb.coinImg)->isActive = active;
	}
	// Boton de iniciar ronda
	mngr_->getComponent<ButtonComponent>(twrSel_.roundButton)->setActive(active);
	mngr_->getComponent<RenderComponent>(twrSel_.roundButton)->isActive = active;
	
	// Boton de pausa
	mngr_->getComponent<ButtonComponent>(pauseButton)->setActive(active);
	mngr_->getComponent<RenderComponent>(pauseButton)->isActive = active;

	// Boton de pausa
	mngr_->getComponent<ButtonComponent>(acelerateButton)->setActive(active);
	mngr_->getComponent<RenderComponent>(acelerateButton)->isActive = active;

	// Background
	mngr_->getComponent<RenderComponent>(twrSel_.background)->isActive = active;
}

Cell* HUDSystem::getCellFromTile(const Vector2D& pos) {
	auto mS = mngr_->getSystem<mapSystem>();
	auto net = mS->getMalla();
	return net->searchCell(pos);
}

void HUDSystem::updateTowerInfo() {
	auto hpCmp = mngr_->getComponent<HealthComponent>(tower_);

	auto bt = mngr_->getComponent<BulletTower>(tower_);
	auto ds = mngr_->getComponent<DiegoSniperTower>(tower_);
	auto st = mngr_->getComponent<SlimeTowerComponent>(tower_);
	auto ft = mngr_->getComponent<PhoenixTower>(tower_);
	auto et = mngr_->getComponent<EnhancerTower>(tower_);
	auto dt = mngr_->getComponent<DirtTower>(tower_);
	auto ct = mngr_->getComponent<CrystalTower>(tower_);
	auto up = mngr_->getComponent<UpgradeTowerComponent>(tower_);

	float range = 100;
	int damage = 0;
	float reloadTime = 0.0;

	if (bt != nullptr) { range = bt->getRange(); damage = bt->getDamage(); reloadTime = bt->getReloadTime(); }
	else if (ds != nullptr) { range = ds->getRange(); damage = ds->getDamage(); reloadTime = ds->getReloadTime(); }
	else if (st != nullptr) { range = st->getRange(); damage = st->getDPS(); reloadTime = st->getReloadTime(); }
	else if (ft != nullptr) { range = ft->getRange(); damage = ft->getDamage(); reloadTime = ft->getCoolingTime(); }
	else if (et != nullptr) { range = et->getRange(); }
	else if (dt != nullptr) { range = dt->getRange(); }
	else if (ct != nullptr) { range = ct->getRange(); reloadTime = ct->getTimeToShield(); }

	mngr_->getComponent<TextComponent>(upM_.hpText)->changeText("HP: " + std::to_string((int)hpCmp->getMaxHealth()));
	mngr_->getComponent<TextComponent>(upM_.damageText)->changeText("DMG: " + std::to_string(damage));
	mngr_->getComponent<TextComponent>(upM_.reloadText)->changeText("RELOAD: " + std::to_string((int)reloadTime));
	mngr_->getComponent<TextComponent>(upM_.upCost)->changeText(std::to_string(up->getUpgradeCost()));

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


