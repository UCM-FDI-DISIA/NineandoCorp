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
			{ xAux + 3, heightH },
			{ floatAt("IconBulletScaleX"), floatAt("IconBulletScaleY")},
			0.0f,
			gameTextures::bulletTowerTexture,
			_grp_HUD_FOREGROUND);
		auto dndBullet = mngr_->addComponent<DragAndDrop>(tb1.img , _twr_BULLET, sdlutils().intConst().at("BalasPrecio"), Height::LOW);
		
		mngr_->addComponent<FramedImage>(tb1.img ,
			intAt("BalasColumns"), intAt("BalasRows"),
			intAt("BalasWidth"), intAt("BalasHeight"),
			0, 0);
		tb1.initialPos = Vector2D( xAux + 3, heightH );
		
		// Set tower price
		tb1.moneyTxt = bS->addText(std::to_string(sdlutils().intConst().at("BalasPrecio")), moneyColor, { xAux - bSize.getX() / 2 , heightH + 50}, {bSize.getX() / 2 , 30});

		//Icono de moneda - TEMPORAL, CAMBIAR MAS TARDE A LA MONEDA INGAME
		tb1.coinImg = bS->addImage(
			{ xAux + bSize.getX() / 4, heightH + 67.5f},
			{30.0f, 30.0f },
			0.0f,
			gameTextures::monedaH,
			_grp_HUD_FOREGROUND);

		twrSel_.buttons[_twr_BULLET] = tb1;
	#pragma endregion

	#pragma region CRISTAL TOWER
		TowerButton tb2;
		tb2.button = bS->addButton({ xAux * 2, heightH},
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::crystal_drag);
		tb2.img = bS->addImage(
			{ xAux * 2 + 3, heightH - 10 },
			{ floatAt("IconCristalScaleX"), floatAt("IconCristalScaleY") },
			0.0,
			cristalTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(tb2.img, _twr_CRISTAL, sdlutils().intConst().at("CristalPrecio"), Height::HIGH);
		mngr_->addComponent<FramedImage>(tb2.img,
			intAt("CristalColumns"), intAt("CristalRows"),
			intAt("CristalWidth"), intAt("CristalHeight"),
			0, 0);
		tb2.initialPos = Vector2D(xAux * 2 + 3, heightH - 10 );

		// Set tower price
		tb2.moneyTxt = bS->addText(std::to_string(sdlutils().intConst().at("CristalPrecio")), moneyColor, { (xAux * 2)  - bSize.getX() / 2 , heightH + 50 }, { bSize.getX() / 2 , 30 });

		//Icono de moneda - TEMPORAL, CAMBIAR MAS TARDE A LA MONEDA INGAME
		tb2.coinImg = bS->addImage(
			{ (xAux * 2) + bSize.getX() / 4 , heightH + 67.5f },
			{ 30.0f, 30.0f },
			0.0f,
			gameTextures::monedaH,
			_grp_HUD_FOREGROUND);

		twrSel_.buttons[_twr_CRISTAL] = tb2;

	#pragma endregion

	#pragma region PHOENIX TOWER
		TowerButton tb3;
		tb3.button = bS->addButton({ xAux * 3, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::fenix_drag);

		tb3.img = bS->addImage(
			{ xAux * 3 + 3, heightH },
			{ floatAt("IconFenixScaleX"), floatAt("IconFenixScaleY") },
			0.0,
			phoenixTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(tb3.img, _twr_FENIX, sdlutils().intConst().at("FenixPrecio"), Height::BOTH);
		mngr_->addComponent<FramedImage>(tb3.img,
			intAt("FenixColumns"), intAt("FenixRows"),
			intAt("FenixWidth"), intAt("FenixHeight"),
			0, 0);

		tb3.initialPos = Vector2D(xAux * 3 + 3, heightH );

		// Set tower price
		tb3.moneyTxt = bS->addText(std::to_string(sdlutils().intConst().at("FenixPrecio")), moneyColor, { (xAux * 3) - bSize.getX() / 2 , heightH + 50 }, { bSize.getX() / 2 , 30 });

		//Icono de moneda - TEMPORAL, CAMBIAR MAS TARDE A LA MONEDA INGAME
		tb3.coinImg = bS->addImage(
			{ (xAux * 3) + bSize.getX() / 4 , heightH + 67.5f },
			{ 30.0f, 30.0f },
			0.0f,
			gameTextures::monedaH,
			_grp_HUD_FOREGROUND);

		twrSel_.buttons[_twr_FENIX] = tb3;
	#pragma endregion

	#pragma region CLAY TOWER
		TowerButton tb4;
		tb4.button = bS->addButton({ xAux * 4, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::clay_drag);
		tb4.img = bS->addImage(
			{ xAux * 4 + 3, heightH },
			{ floatAt("IconClayScaleX"), floatAt("IconClayScaleY") },
			0.0,
			clayTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(tb4.img, _twr_CLAY, sdlutils().intConst().at("ArcillaPrecio"), Height::PATH);
		mngr_->addComponent<FramedImage>(tb4.img,
			intAt("ArcillaColumns"), intAt("ArcillaRows"),
			intAt("ArcillaWidth"), intAt("ArcillaHeight"),
			0, 0);

		tb4.initialPos = Vector2D( xAux * 4 + 3, heightH );

		// Set tower price
		tb4.moneyTxt = bS->addText(std::to_string(sdlutils().intConst().at("ArcillaPrecio")), moneyColor, { (xAux * 4) - bSize.getX() / 2 , heightH + 50 }, { bSize.getX() / 2 , 30 });

		//Icono de moneda - TEMPORAL, CAMBIAR MAS TARDE A LA MONEDA INGAME
		tb4.coinImg = bS->addImage(
			{ (xAux * 4) + bSize.getX() / 4 , heightH + 67.5f },
			{ 30.0f, 30.0f },
			0.0f,
			gameTextures::monedaH,
			_grp_HUD_FOREGROUND);

		twrSel_.buttons[_twr_CLAY] = tb4;
	#pragma endregion

	#pragma region SNIPER TOWER
		TowerButton tb5;
		tb5.button = bS->addButton({ xAux * 5, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::sniper_drag);

		tb5.img = bS->addImage(
			{ xAux * 5 + 3, heightH },
			{ floatAt("IconSniperScaleX"), floatAt("IconSniperScaleY") },
			0.0,
			sniperTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(tb5.img, _twr_DIEGO, sdlutils().intConst().at("DiegoSniperPrecio"), Height::HIGH);
		mngr_->addComponent<FramedImage>(tb5.img,
			intAt("DiegoSniperColumns"), intAt("DiegoSniperRows"),
			intAt("DiegoSniperWidth"), intAt("DiegoSniperHeight"),
			0, 0);

		tb5.initialPos = Vector2D( xAux * 5 + 3, heightH );

		// Set tower price
		tb5.moneyTxt = bS->addText(std::to_string(sdlutils().intConst().at("DiegoSniperPrecio")), moneyColor, { (xAux * 5) - bSize.getX() / 2 , heightH + 50 }, { bSize.getX() / 2 , 30 });

		//Icono de moneda - TEMPORAL, CAMBIAR MAS TARDE A LA MONEDA INGAME
		tb5.coinImg = bS->addImage(
			{ (xAux * 5) + bSize.getX() / 4 , heightH + 67.5f },
			{ 30.0f, 30.0f },
			0.0f,
			gameTextures::monedaH,
			_grp_HUD_FOREGROUND);

		twrSel_.buttons[_twr_DIEGO] = tb5;
	#pragma endregion
	
	#pragma region SLIME TOWER
		TowerButton tb6;
		tb6.button = bS->addButton({ xAux * 6, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::slime_drag);

		tb6.img = bS->addImage(
			{ xAux * 6 + 3, heightH },
			{ floatAt("IconSlimeScaleX"), floatAt("IconSlimeScaleY") },
			0.0,
			slimeTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(tb6.img, _twr_SLIME, sdlutils().intConst().at("SlimePrecio"), Height::LOW);
		mngr_->addComponent<FramedImage>(tb6.img,
			intAt("SlimeColumns"), intAt("SlimeRows"),
			intAt("SlimeWidth"), intAt("SlimeHeight"),
			0, 0);

		tb6.initialPos =  Vector2D( xAux * 6 + 3, heightH );

		// Set tower price
		tb6.moneyTxt = bS->addText(std::to_string(sdlutils().intConst().at("SlimePrecio")), moneyColor, { (xAux * 6) - bSize.getX() / 2 , heightH + 50 }, { bSize.getX() / 2 , 30 });

		//Icono de moneda - TEMPORAL, CAMBIAR MAS TARDE A LA MONEDA INGAME
		tb6.coinImg = bS->addImage(
			{ (xAux * 6) + bSize.getX() / 4 , heightH + 67.5f },
			{ 30.0f, 30.0f },
			0.0f,
			gameTextures::monedaH,
			_grp_HUD_FOREGROUND);

		twrSel_.buttons[_twr_SLIME] = tb6;
	#pragma endregion

	#pragma region POWER TOWER
		TowerButton tb7;
		tb7.button = bS->addButton({ xAux * 7, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::enhancer_drag);

		tb7.img = bS->addImage(
			{ xAux * 7 + 3, heightH - 4},
			{ floatAt("IconPotenciadorScaleX"), floatAt("IconPotenciadorScaleY") },
			0.0,
			boosterTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(tb7.img, _twr_POWER, sdlutils().intConst().at("PotenciadoraPrecio"), Height::BOTH);
		mngr_->addComponent<FramedImage>(tb7.img,
			intAt("PotenciadoraColumns"), intAt("PotenciadoraRows"),
			intAt("PotenciadoraWidth"), intAt("PotenciadoraHeight"),
			0, 0);

		tb7.initialPos = Vector2D( xAux * 7 + 3 , heightH - 4 );
		// Set tower price
		tb7.moneyTxt = bS->addText(std::to_string(sdlutils().intConst().at("PotenciadoraPrecio")), moneyColor, { (xAux * 7) - bSize.getX() / 2 , heightH + 50 }, { bSize.getX() / 2 , 30 });

		//Icono de moneda - TEMPORAL, CAMBIAR MAS TARDE A LA MONEDA INGAME
		tb7.coinImg = bS->addImage(
			{ (xAux * 7) + bSize.getX() / 4 , heightH + 67.5f },
			{ 30.0f, 30.0f },
			0.0f,
			gameTextures::monedaH,
			_grp_HUD_FOREGROUND);

		twrSel_.buttons[_twr_POWER] = tb7;
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
		dragTowerIcon(twrSel_.buttons[m.drag_data.towerId].img);
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
	*	BOTON DE VENDER
	*/
	Message m1;
	m1.id = _m_SELL_TOWER;
	m1.sell_tower_data.twr = twr;
	int cost = mngr_->getComponent<DragAndDrop>(twrSel_.buttons[upCmp->id_].img)->getCost();
	m1.sell_tower_data.money = (cost * 75) / 100 ;

	Vector2D posC = { pos.getX() + 390 + cameraOffset_->x, pos.getY() + cameraOffset_->y };
	upM_.sellButton = bS->addButton(posC + offset,
		{ 150.0f, 60.0f },
		sell, sell_hover, ButtonTypes::sell_tower, 0,
		m1
	);

	/**
	*	BOTON DE SALIR
	*/
	Vector2D posD = { pos.getX() + 460.0f + cameraOffset_->x, pos.getY() - 105.0f + cameraOffset_->y };
	upM_.exitButton = bS->addButton(posD + offset,
		{ 40.0f , 40.0f },
		gameTextures::close, gameTextures::close_hover, ButtonTypes::exit_up_menu);
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
	mngr_->refresh();

	mngr_->deleteHandler(hId, upM_.sellButton);
	mngr_->deleteHandler(hId, upM_.exitButton);
	mngr_->deleteHandler(hId, upM_.upgradeButton);
	mngr_->deleteHandler(hId, upM_.background);

	upM_ = UpgradeMenu();

}

void HUDSystem::showSelector(bool active) {
	// TowerButtons
	for (auto tb : twrSel_.buttons) {
		//Boton
		auto b = tb.button;
		mngr_->getComponent<ButtonComponent>(b)->setActive(active);
		mngr_->getComponent<RenderComponent>(b)->isActive = active;
		//Icono torre
		mngr_->getComponent<RenderComponent>(tb.img)->isActive = active;
		//Texto de dinero
		mngr_->getComponent<TextComponent>(tb.moneyTxt)->isActive = active;
		mngr_->getComponent<RenderComponent>(tb.coinImg)->isActive = active;
	}
	// Boton de iniciar ronda
	mngr_->getComponent<ButtonComponent>(twrSel_.roundButton)->setActive(active);
	mngr_->getComponent<RenderComponent>(twrSel_.roundButton)->isActive = active;
	
	// Background
	mngr_->getComponent<RenderComponent>(twrSel_.background)->isActive = active;
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


