#include "ButtonSystem.h"
#include "../game/Game.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"
#include "../components/TextComponent.h"
#include "../components/FramedImage.h"
#include "../components/LimitedTime.h"

ButtonSystem::ButtonSystem(hdlrId_type but_id) :
	hdlr_but_id(but_id), money_(0), HMoney_(0), moneyText_(nullptr), bulletMoneyText_(nullptr), diegoMoneyText_(nullptr), slimeMoneyText_(nullptr), cristalMoneyText_(nullptr),
	fenixMoneyText_(nullptr), enhancerMoneyText_(nullptr), dirtMoneyText_(nullptr), nexusImage_(nullptr), nexusLvl_(nullptr), bulletImage_(nullptr), diegoImage_(nullptr), slimeImage_(nullptr), cristalImage_(nullptr),
	fenixImage_(nullptr), enhancerImage_(nullptr), dirtImage_(nullptr) {
	mActive = true;
	resolutionActive = false;
	isPlayState = false;
	numAcelButs = 3;
	cauntAcelButs = 1;
	font_size_coin_HUD = { 24.0f, 50.0f };
	font_size_Hcoin_nexus = { 40.0f, 80.0f };
	twr_img_separation = 325.0f;
	info_separation = 45.0f;
	towerImagesSize = { 80.5f, 112.0f };

	//rellenar la lista de costes
	costs[_twr_BULLET] = sdlutils().intConst().at("BalasPrecio");
	costs[_twr_FENIX] = sdlutils().intConst().at("FenixPrecio");
	costs[_twr_DIEGO] = sdlutils().intConst().at("DiegoSniperPrecio");
	costs[_twr_CLAY] = sdlutils().intConst().at("ArcillaPrecio");
	costs[_twr_CRISTAL] = sdlutils().intConst().at("CristalPrecio"); 
	costs[_twr_POWER] = sdlutils().intConst().at("PotenciadoraPrecio");
	costs[_twr_SLIME] = sdlutils().intConst().at("SlimePrecio");
}

ButtonSystem::~ButtonSystem(){
}
void ButtonSystem::update () {
	if (mActive) {
		manageButtons();
		manageKeys();
	}
	else {
		managePauseButtons();
	}
}


void ButtonSystem::initSystem() {
}
void ButtonSystem::receive(const Message& m){
	switch (m.id) {
	case _m_ADD_MONEY:
		money_ += m.money_data.money;
		updateText(money_, font_size_coin_HUD);
		break;
	case _m_START_MENU:
		HMoney_ = m.money_data.money;
		game().getSaveGame()->setHCoins(HMoney_);
		generateHMoneyText();
		generateUpgradeMoneyTexts();
		break;
	case _m_START_GAME:
		money_ = m.start_game_data.money;
		OnStartGame();
		break;
	case _m_ABLEBUTTONS:
		enableAllButton(m.able_buttons_data.isAble, m.able_buttons_data.buttonId);
		break;
	case _m_ADD_TEXT:
		showTempText(m.add_text_data.txt,  
				 m.add_text_data.color, 
				 m.add_text_data.pos,	 
			     m.add_text_data.scale,
				 m.add_text_data.time
					);
		break;
	case _m_CONFIG:
		mActive = true;
		break;
	case _m_PAUSE:
		mActive = !m.start_pause.onPause;
		break;
	case _m_ISPLAYSTATE:
		isPlayState = m.start_game_data.isPlayState;
		break;
	case _m_WAVE_START:
		canStartWave = !m.start_wave.play;
		break;
	default:
		break;
	}
}

void ButtonSystem::manageKeys() {
	sdlutils().soundEffects().at("button").setChannelVolume(game().CalculoVolumenEfectos(), 1);
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_Q) && hdlr_but_id == hdlrId::_hdlr_BUTTON_PLAY) {
		sdlutils().soundEffects().at("button").play(0, 1);
		sdlutils().soundEffects().at("button").pauseAllChannels();
		Pause(true);
	}
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_SPACE) && hdlr_but_id == hdlrId::_hdlr_BUTTON_PLAY) {
		sdlutils().soundEffects().at("button").play(0, 1);
		switch (cauntAcelButs)
		{
		case 1:
			Acelerate(1.5f);
			break;
		case 2:
			Acelerate(2.0f);
			break;
		case 3:
			Acelerate(1.0f);
			break;
		default:
			break;
		}

		if (cauntAcelButs < numAcelButs) {
			cauntAcelButs++;
		}
		else {
			cauntAcelButs = 1;
		}
	}
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_RETURN) && canStartWave && hdlr_but_id == hdlrId::_hdlr_BUTTON_PLAY) {
		startWave();
		canStartWave = false;
		sdlutils().soundEffects().at("button").play(0, 1);
	}
}

void ButtonSystem::manageButtons() {
	//Posicion actual del mouse
	Vector2D pos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };
	auto buts = mngr_->getHandler(hdlr_but_id);
	//hover 
	for (auto en : buts) {
		if (en != nullptr) {
			if (mngr_->isAlive(en)) {
				RenderComponent* rC = mngr_->getComponent<RenderComponent>(en);
				if (mngr_->hasComponent<ButtonComponent>(en)) {
					ButtonComponent* bC = mngr_->getComponent<ButtonComponent>(en);
					if (bC->isActive()) {
						if (bC->hover(pos)) rC->setTexture(bC->getHover());
						else rC->setTexture(bC->getTexture());
					}
			}
			}
		}
	}

	//click
	if (ih().mouseButtonEvent()) {

		if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1) {
			//Recorre lista de entities de tipo HUD_FOREGROUND
			for (auto en : mngr_->getHandler(hdlr_but_id)) {
				auto bC = mngr_->getComponent<ButtonComponent>(en);
				SliderComponent* slider = mngr_->getComponent<SliderComponent>(en);
				auto tR = mngr_->getComponent<Transform>(en);
				if (en != nullptr && bC != nullptr) {
					//comprueba la id del button y si no es none llama a la funcion correspondiente
					auto type = bC->isPressed(pos);
					if (type != ButtonTypes::none) {
						callFunction(type, en);
						break;
					}
				}
				else if (en != nullptr && slider != nullptr && tR != nullptr) {
					if (slider->isPressed(pos)) {
						slider->setDragging(!slider->getDragging());
						// Actualiza la posición del slider
						float posX = pos.getX() - tR->getWidth() / 2; // Centra el slider en el mouse
						// Asegúrate de que la nueva posición esté dentro de los límites
						posX = std::max(slider->getMin(), std::min(posX, slider->getMax() - tR->getWidth()));
						tR->setX(posX);
						// Calcular el valor del volumen en función de la posición del slider dentro de los límites relativos
						float relativeValue = (posX - slider->getMin()) / (slider->getMax() - tR->getScale()->getX() - slider->getMin());
						float volume = relativeValue * slider->getRelativeMax(); // Escalamos de 0 a 100

						
						//cout << volume << endl;
						if (slider->getSlider() == general) {
							game().instance()->setSoundGeneral(volume);
							game().instance()->setNewMaxGeneral(slider->getMax() - posX );
							game().instance()->setNewMinGeneral(posX  - slider->getMin());
							sdlutils().musics().at("Soundtrack").setMusicVolume(game().CalculoVolumenMusica());
						}
						else if (slider->getSlider() == music) {
							game().instance()->setSoundMusic(volume);
							game().instance()->setNewMaxMusic(slider->getMax() - posX);
							game().instance()->setNewMinMusic(posX - slider->getMin());
							sdlutils().musics().at("Soundtrack").setMusicVolume(game().CalculoVolumenMusica());
						}
						else if (slider->getSlider() == effects) {
							game().instance()->setSoundEffect(volume);
							game().instance()->setNewMaxEffects(slider->getMax() - posX);
							game().instance()->setNewMinEffects(posX - slider->getMin());
						}
						
					}
				}
			}
		}
		
	}
	else {
		// Si el botón del ratón no está siendo presionado, actualiza la posición del slider
		for (auto en : mngr_->getHandler(hdlr_but_id)) {
			SliderComponent* slider = mngr_->getComponent<SliderComponent>(en);
			auto tR = mngr_->getComponent<Transform>(en);
			if (slider != nullptr && tR != nullptr && slider->getDragging()) {
				Vector2D pos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };
				float posX = pos.getX() - tR->getWidth() / 2; // Centra el slider en el mouse
				posX = std::max(slider->getMin(), std::min(posX, slider->getMax() - tR->getWidth()));
				tR->setX(posX);
			}
		}
	}
	
	//update de texto con limitTime
	auto txts = mngr_->getEntities(_grp_TEXTS);
	for (auto txt : txts) {
		auto limT = mngr_->getComponent<LimitedTime>(txt);
		if (limT != nullptr) {
			limT->update();
		}
	}
}
void ButtonSystem::managePauseButtons() {
	//Posicion actual del mouse
	Vector2D pos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };
	auto buts = mngr_->getHandler(_hdlr_BUTTON_PAUSE);
	//hover 
	for (auto en : buts) {
		if (en != nullptr) {

			ButtonComponent* bC = mngr_->getComponent<ButtonComponent>(en);
			RenderComponent* rC = mngr_->getComponent<RenderComponent>(en);
			if (bC != nullptr) {
				if (bC->isActive()) {
					if (bC->hover(pos)) rC->setTexture(bC->getHover());
					else rC->setTexture(bC->getTexture());
				}
			}
		}
	}

	//click
	if (ih().mouseButtonEvent()) {

		if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1) {

			//Recorre lista de entities de tipo HUD_FOREGROUND
			for (auto en : mngr_->getHandler(_hdlr_BUTTON_PAUSE)) {
				auto bC = mngr_->getComponent<ButtonComponent>(en);
				if (en != nullptr && bC != nullptr) {
					//comprueba la id del button y si no es none llama a la funcion correspondiente
					auto type = bC->isPressed(pos);
					if (type != ButtonTypes::none) {
						callFunction(type, en);
						break;
					}
				}
			}
		}
	}
}

#pragma region FUNCIONES DE BOTONES

void ButtonSystem::sellTower(Entity* twr)
{
	
}

//Todas las funciones de los botones del juego
	void ButtonSystem::callFunction(ButtonTypes type, Entity* bC) {
		// Incluye la id del button para incluir 
		sdlutils().soundEffects().at("button").setChannelVolume(game().CalculoVolumenEfectos(), 1);
		int lvl;
		switch (type)
		{
		case back_to_menu:
			game().SetDelay(1.0f);
			game().changeState<MainMenuState>();
			sdlutils().soundEffects().at("button").play(0, 1);
			break;
		case backToMenu_warning_button:
			Warning("Level progress will be lost. Back to menu?", back_to_menu);
			sdlutils().soundEffects().at("button").play(0, 1);
			break;
		case exit_button:
			game().exitGame();
			sdlutils().soundEffects().at("button").play(0, 1);
			break;
		case exit_warning_button:
			Warning("Level progress will be lost. Exit?", exit_button);
			sdlutils().soundEffects().at("button").play(0, 1);
			break;
		case warning_return_button:
			Warning("", warning_return_button);
			sdlutils().soundEffects().at("button").play(0, 1);
			break;
		case selector_main:
			loadLevelSelector();
			pauseAllButtons();
			sdlutils().soundEffects().at("button").play(0, 1);
			break;
		case enemies_main:
			EnemyBook();
			pauseAllButtons();
			sdlutils().soundEffects().at("AbrirEnemiesBook").play(0, 1);
			break;
		case back_selector:
			backToMainMenu();
			sdlutils().soundEffects().at("button").play(0, 1);
			
			break;
		case config:
			Config();
			sdlutils().soundEffects().at("button").play(0, 1);
			break;
		case full_screen:
			sdlutils().toggleFullScreen();
			game().instance()->setFullScreen();
			if (game().instance()->getFullScreen()) {
				mngr_->getComponent<ButtonComponent>(bC)->setTexture(check);
				mngr_->getComponent<ButtonComponent>(bC)->setHover(check_hover);
			}
			else {
				mngr_->getComponent<ButtonComponent>(bC)->setTexture(button);
				mngr_->getComponent<ButtonComponent>(bC)->setHover(button_hover);
			}
			
			break;
		case changeResolution:
			stopConfig(bC);
			sdlutils().soundEffects().at("button").play(0, 1);
			break;
		case level_selected:
			startGame(bC);
			sdlutils().soundEffects().at("button").play(0, 1);
			break;
		case play_wave:
			startWave();
			sdlutils().soundEffects().at("button").play(0, 1);
			break;
		case pause_main:
			sdlutils().soundEffects().at("button").pauseAllChannels();
			Pause(true);
			sdlutils().soundEffects().at("button").play(0, 1);
			break;
		case resume_main:
			sdlutils().soundEffects().at("button").resumeAllChannels();
			game().popState();
			Pause(false);
			sdlutils().soundEffects().at("button").play(0, 1);
			break;
		case acelerate:
			sdlutils().soundEffects().at("button").play(0, 1);
			switch (cauntAcelButs)
			{
			case 1:
				Acelerate(1.5f);
				break;
			case 2:
				Acelerate(2.0f);
				break;
			case 3:
				Acelerate(1.0f);
				break;
			default:
				break;
			}

			if (cauntAcelButs < numAcelButs) { 
				cauntAcelButs++; 
			}
			else { 
				cauntAcelButs = 1; 
			}
			break;
		case enemybook:
			sdlutils().soundEffects().at("AbrirEnemiesBook").play(0, 1);
			pauseAllButtons();
			mngr_->send(mngr_->getComponent<ButtonComponent>(bC)->getMessage());
			break;
		case enemybookPopAbility:
			sdlutils().soundEffects().at("AbrirEnemiesBook").play(0, 1);
			mngr_->send(mngr_->getComponent<ButtonComponent>(bC)->getMessage());
			break;
		/*--- MEJORAS DEL MENU ---*/
		case upgrade_nexus:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_NEXUS];
			if( lvl < 4)
				upgradeTower(_twr_NEXUS, "precioHNexoLvl" + std::to_string(lvl), bC);
			break;
		case upgrade_crystal_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_CRISTAL];
			if (lvl < towerLevelMax - 1)
				upgradeTower(_twr_CRISTAL, "precioHCristalLvl" + std::to_string(lvl), bC);
			break;
		case upgrade_slime_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_SLIME];
			if (lvl < towerLevelMax - 1)
				upgradeTower(_twr_SLIME, "precioHSlimeLvl" + std::to_string(lvl), bC);
			break;
		case upgrade_bullet_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_BULLET];
			if (lvl < towerLevelMax - 1)
				upgradeTower(_twr_BULLET, "precioHBalasLvl" + std::to_string(lvl), bC);
			break;
		case upgrade_sniper_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_DIEGO];
			if (lvl < towerLevelMax - 1)
				upgradeTower(_twr_DIEGO, "precioHDiegoLvl" + std::to_string(lvl), bC);
			break;
		case upgrade_fenix_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_FENIX];
			if (lvl < towerLevelMax - 1)
				upgradeTower(_twr_FENIX, "precioHFenixLvl" + std::to_string(lvl), bC);
			break;
		case upgrade_clay_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_CLAY];
			if (lvl < towerLevelMax - 1)
				upgradeTower(_twr_CLAY, "precioHArcillaLvl" + std::to_string(lvl), bC);
			break;
		case upgrade_enhancer_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_POWER];
			if (lvl < towerLevelMax - 1)
				upgradeTower(_twr_POWER, "precioHPotenciadoraLvl" + std::to_string(lvl), bC);
			break;
		case show_info:
			mngr_->send(mngr_->getComponent<ButtonComponent>(bC)->getMessage());
			break;

		/*--- SELECCIÓN DE TORRES PARA DRAG ---*/
		case crystal_drag:
			dragTower(_twr_CRISTAL);
			break;
		case bullet_drag:
			dragTower(_twr_BULLET);
			break;
		case fenix_drag:
			dragTower(_twr_FENIX);
			break;
		case clay_drag:
			dragTower(_twr_CLAY);
			break;
		case sniper_drag:
			dragTower(_twr_DIEGO);
			break;
		case enhancer_drag:
			dragTower(_twr_POWER);
			break;
		case slime_drag:
			dragTower(_twr_SLIME);
			break;
		case sell_tower:
			sdlutils().soundEffects().at("SellTower").play(0, 1);
			mngr_->send(mngr_->getComponent<ButtonComponent>(bC)->getMessage());
			break;

		/*--- UPGRADE TOWER ---*/
		case upgrade_tower: 
			mngr_->send(mngr_->getComponent<ButtonComponent>(bC)->getMessage());
			break;
		case exit_up_menu:
			sdlutils().soundEffects().at("button").play(0, 1);
			exitUpMenu();
			break;

		/*--- ChangeControls ---*/
		case changeControls:
			mngr_->send(mngr_->getComponent<ButtonComponent>(bC)->getMessage());
			break;
		/*----------------------------------------*/
		}
	}
	void ButtonSystem::setUpgradeTex(Entity* bC) {
		ButtonComponent* btComp = mngr_->getComponent<ButtonComponent>(bC);
		if (btComp->getTexture() == buy) {
			btComp->setTexture(upgrade);
			btComp->setHover(upgrade_hover);
		}
	}
	void ButtonSystem::pauseAllButtons() {
		for (auto but : mngr_->getHandler(hdlr_but_id)) {
			auto bC = mngr_->getComponent<ButtonComponent>(but);
			if(bC != nullptr) bC->setActive(false);
		}
	}

	void ButtonSystem::enableAllButton(bool b, grpId bType)
	{
		for (auto but : mngr_->getEntities(bType)) {
			auto bC = mngr_->getComponent<ButtonComponent>(but);
			if (bC != nullptr) bC->setActive(b);
		}
	}

	
	void ButtonSystem::loadLevelSelector() {
		Message m;
		m.id = _m_LEVEL_SELECTOR;
		mngr_->send(m, true);
	}
	void ButtonSystem::Pause(bool onPause) {
		Message m;
		m.id = _m_PAUSE;
		m.start_pause.onPause = onPause;
		mngr_->send(m, true);
	}
	void ButtonSystem::Acelerate(float _acel) {
		Message m;
		m.id = _m_ACELERATE;
		m.acelerate_plus.acel = _acel;
		mngr_->send(m, true);
	}
	void ButtonSystem::Warning(string text, ButtonTypes butTyp) {
		Message m;
		m.id = _m_WARNING;
		m.warning_info.text = text;
		m.warning_info.butTyp = butTyp;
		mngr_->send(m, true);
	}
	void ButtonSystem::Config() {
		mngr_->getComponent<TextComponent>(moneyText_)->isActive = false;
		Message m;
		m.id = _m_CONFIG;
		mngr_->send(m, true);
	}
	void ButtonSystem::stopConfig( Entity* bC) {
		resolutionActive = !resolutionActive;
		auto settings = mngr_->getHandler(_hdlr_BUTTON_CONFIG);
		for (auto en : settings) {
			ButtonComponent* btC = mngr_->getComponent<ButtonComponent>(en);
			if(btC != nullptr)
				btC->setActive(!btC->isActive());
		}
		if (resolutionActive) {
			Message m;
			m.id = _m_CHANGE_RESOLUTION;
			m.settings_data.resolutions = 3;
			mngr_->send(m);
		}
		else {
			ButtonComponent* btC = mngr_->getComponent<ButtonComponent>(bC);
			sdlutils().setResolution(btC->getWidth(), btC->getHeight());
			if (!isPlayState) {
				for (auto en : mngr_->getHandler(_hdlr_BUTTON_MAIN)) {
					mngr_->setAlive(en, false);
				}
				mngr_->refresh();
				mngr_->deleteAllHandlers(_hdlr_BUTTON_MAIN);
			}
			else {
				for (auto en : mngr_->getHandler(_hdlr_BUTTON_PLAY)) {
					mngr_->setAlive(en, false);
				}
				
				mngr_->deleteAllHandlers(_hdlr_BUTTON_PLAY);
				for (auto en : mngr_->getHandler(_hdlr_BUTTON_ACELERATE)) {
					mngr_->setAlive(en, false);
				}
				mngr_->refresh();
				mngr_->deleteAllHandlers(_hdlr_BUTTON_ACELERATE);

				isPlayState = false;
			}
			for (auto en : mngr_->getHandler(_hdlr_BUTTON_CONFIG)) {
				mngr_->setAlive(en, false);
			}
			mngr_->refresh();
			mngr_->deleteAllHandlers(_hdlr_BUTTON_CONFIG);
			
			mngr_->getSystem<ConfigSystem>()->initSystem();
			mngr_->refresh();
		}
		
	}
	void ButtonSystem::EnemyBook() {
		Message m;
		m.id = _m_ENEMY_BOOK;
		mngr_->send(m, true);
	}
	void ButtonSystem::backToMainMenu() {
		mngr_->getComponent<TextComponent>(moneyText_)->isActive = true;
		Message m1;
		m1.id = _m_BACK_TO_MAINMENU;
		mngr_->send(m1);
	}
	void ButtonSystem::startGame(Entity* bC) {
		auto butC = mngr_->getComponent<ButtonComponent>(bC);
		Message m;
		m.id = _m_LEVEL_SELECTED;
		m.start_game_data.level = butC->getLevel();
		mngr_->send(m);
	}
	void ButtonSystem::exitUpMenu()
	{
		Message m;
		m.id = _m_EXIT_UP_MENU;
		mngr_->send(m);
	}
	void ButtonSystem::startWave() {
		Message m;
		m.id = _m_WAVE_START;
		m.start_wave.play = true;
		mngr_->send(m);
	}
	void ButtonSystem::upgradeTower(twrId t, string idPrecioJSON, Entity* bC) {
		if (HMoney_ - sdlutils().intConst().at(idPrecioJSON) >= 0) {
			throwUpgradeAnim(mngr_->getComponent<Transform>(bC)->getPosition());
			sdlutils().soundEffects().at("MejoraComprada").play(0, 1);
			setUpgradeTex(bC);
			HMoney_ -= sdlutils().intConst().at(idPrecioJSON);
			updateText(HMoney_, font_size_Hcoin_nexus);
			game().getSaveGame()->setHCoins(HMoney_);
			Message m;
			m.id = _m_UPGRADE_TOWER;
			m.upgrade_tower.towerId = t;
			mngr_->send(m);
		}
		else {
			sdlutils().soundEffects().at("DineroInsuficiente").play(0, 1);
		}
		string towerPriceString;
		int towerLvl = game().getSaveGame()->getTurretsLevels()[t];
		int price;
		switch (t) {
		case _twr_BULLET:
			if (towerLvl < 5) {
				towerPriceString = "precioHBalasLvl" + std::to_string(towerLvl);
				price = intAt(towerPriceString);
				auto fi = mngr_->getComponent<FramedImage>(bulletImage_);
				if (fi != nullptr)
				fi->setCurrentFrame(towerLvl - 1);
				mngr_->getComponent<TextComponent>(bulletMoneyText_)->changeText(std::to_string(price));
				mngr_->getComponent<TextComponent>(bulletLvlText_)->changeText("LVL: " + std::to_string(towerLvl));
				if (towerLvl == 4) {
					mngr_->setAlive(bulletMoneyText_, false);
					mngr_->setAlive(bulletCoin_, false);
					mngr_->deleteHandler(hdlr_but_id, bulletMoneyText_);
					mngr_->deleteHandler(hdlr_but_id, bulletCoin_);
					std::basic_string s = "LVL: MAX.";
					mngr_->getComponent<TextComponent>(bulletLvlText_)->changeText(s);
					mngr_->getComponent<Transform>(bulletLvlText_)->setScale({ s.size() * font_size.getX(), font_size.getY() });
				}
			}
			break;
		case _twr_CLAY:
			if (towerLvl < 5) {
				towerPriceString = "precioHArcillaLvl" + std::to_string(towerLvl);
				price = intAt(towerPriceString);
				auto fi = mngr_->getComponent<FramedImage>(dirtImage_);
				if (fi != nullptr)
				fi->setCurrentFrame(towerLvl - 1);
				mngr_->getComponent<TextComponent>(dirtMoneyText_)->changeText(std::to_string(price));
				mngr_->getComponent<TextComponent>(dirtLvlText_)->changeText("LVL: " + std::to_string(towerLvl));
				if (towerLvl == 4) {
					mngr_->setAlive(dirtMoneyText_, false);	
					mngr_->setAlive(dirtCoin_, false);
					mngr_->deleteHandler(hdlr_but_id, dirtMoneyText_);
					mngr_->deleteHandler(hdlr_but_id, dirtCoin_);
					std::basic_string s = "LVL: MAX.";
					mngr_->getComponent<TextComponent>(dirtLvlText_)->changeText(s);
					mngr_->getComponent<Transform>(dirtLvlText_)->setScale({ s.size() * font_size.getX(), font_size.getY() });
				}
			}
			break;
		case _twr_CRISTAL:
			if (towerLvl == 1) {
				if (!mngr_->hasComponent<FramedImage>(cristalImage_))mngr_->addComponent<FramedImage>(cristalImage_, intAt("CristalColumns"), intAt("CristalRows"), intAt("CristalWidth"), intAt("CristalHeight"), 0, 0);
				mngr_->getComponent<RenderComponent>(cristalImage_)->setTexture(cristalTowerTexture);
			}
			if (towerLvl < 5) {
				towerPriceString = "precioHCristalLvl" + std::to_string(towerLvl);
				price = intAt(towerPriceString);
				auto fi = mngr_->getComponent<FramedImage>(cristalImage_);
				if (fi != nullptr)
				fi->setCurrentFrame(towerLvl - 1);
				mngr_->getComponent<TextComponent>(cristalMoneyText_)->changeText(std::to_string(price));
				mngr_->getComponent<TextComponent>(cristalLvlText_)->changeText("LVL: " + std::to_string(towerLvl));
				if (towerLvl == 4) {
					mngr_->setAlive(cristalMoneyText_, false);
					mngr_->setAlive(cristalCoin_, false);
					mngr_->deleteHandler(hdlr_but_id, cristalMoneyText_);
					mngr_->deleteHandler(hdlr_but_id, cristalCoin_);
					std::basic_string s = "LVL: MAX.";
					mngr_->getComponent<TextComponent>(cristalLvlText_)->changeText(s);
					mngr_->getComponent<Transform>(cristalLvlText_)->setScale({ s.size() * font_size.getX(), font_size.getY() });
				}
			}
			break;
		case _twr_POWER:
			if (towerLvl == 1) {
				if (!mngr_->hasComponent<FramedImage>(enhancerImage_))mngr_->addComponent<FramedImage>(enhancerImage_, intAt("PotenciadoraColumns"), intAt("PotenciadoraRows"), intAt("PotenciadoraWidth"), intAt("PotenciadoraHeight"), 0, 0);
				mngr_->getComponent<RenderComponent>(enhancerImage_)->setTexture(boosterTowerTexture);
			}
			if (towerLvl < 5) {
				towerPriceString = "precioHPotenciadoraLvl" + std::to_string(towerLvl);
				price = intAt(towerPriceString);
				auto fi = mngr_->getComponent<FramedImage>(enhancerImage_);
				if(fi != nullptr)
					fi->setCurrentFrame(towerLvl - 1);
				mngr_->getComponent<TextComponent>(enhancerMoneyText_)->changeText(std::to_string(price));
				mngr_->getComponent<TextComponent>(enhancerLvlText_)->changeText("LVL: " + std::to_string(towerLvl));
				if (towerLvl == 4) {
					mngr_->setAlive(enhancerMoneyText_, false);
					mngr_->setAlive(enhancerCoin_, false);
					mngr_->deleteHandler(hdlr_but_id, enhancerMoneyText_);
					mngr_->deleteHandler(hdlr_but_id, enhancerCoin_);
					std::basic_string s = "LVL: MAX.";
					mngr_->getComponent<TextComponent>(enhancerLvlText_)->changeText(s);
					mngr_->getComponent<Transform>(enhancerLvlText_)->setScale({ s.size() * font_size.getX(), font_size.getY() });
				}
			}
			break;
		case _twr_DIEGO:
			if (towerLvl == 1) {
				if (!mngr_->hasComponent<FramedImage>(diegoImage_))mngr_->addComponent<FramedImage>(diegoImage_, intAt("DiegoSniperColumns"), intAt("DiegoSniperRows"), intAt("DiegoSniperWidth"), intAt("DiegoSniperHeight"), 0, 0);
				mngr_->getComponent<RenderComponent>(diegoImage_)->setTexture(sniperTowerTexture);
			}
			if (towerLvl < 5) {
				towerPriceString = "precioHDiegoLvl" + std::to_string(towerLvl);
				price = intAt(towerPriceString);
				auto fi = mngr_->getComponent<FramedImage>(diegoImage_);
				if (fi != nullptr)
				fi->setCurrentFrame(towerLvl - 1);
				mngr_->getComponent<TextComponent>(diegoMoneyText_)->changeText(std::to_string(price));
				mngr_->getComponent<TextComponent>(diegoLvlText_)->changeText("LVL: " + std::to_string(towerLvl));
				if (towerLvl == 4) {
					mngr_->setAlive(diegoMoneyText_, false);
					mngr_->setAlive(diegoCoin_, false);
					mngr_->deleteHandler(hdlr_but_id, diegoMoneyText_);
					mngr_->deleteHandler(hdlr_but_id, diegoCoin_);
					std::basic_string s = "LVL: MAX.";
					mngr_->getComponent<TextComponent>(diegoLvlText_)->changeText(s);
					mngr_->getComponent<Transform>(diegoLvlText_)->setScale({ s.size() * font_size.getX(), font_size.getY() });
				}
			}
			break;
		case _twr_FENIX:
			if (towerLvl == 1) {
				if (!mngr_->hasComponent<FramedImage>(fenixImage_))mngr_->addComponent<FramedImage>(fenixImage_, intAt("FenixColumns"), intAt("FenixRows"), intAt("FenixWidth"), intAt("FenixHeight"), 0, 0);
				mngr_->getComponent<RenderComponent>(fenixImage_)->setTexture(phoenixTowerTexture);
			}
			if (towerLvl < 5) {
				towerPriceString = "precioHFenixLvl" + std::to_string(towerLvl);
				price = intAt(towerPriceString);
				auto fi = mngr_->getComponent<FramedImage>(fenixImage_);
				if (fi != nullptr)
				fi->setCurrentFrame(towerLvl - 1);
				mngr_->getComponent<TextComponent>(fenixMoneyText_)->changeText(std::to_string(price));
				mngr_->getComponent<TextComponent>(fenixLvlText_)->changeText("LVL: " + std::to_string(towerLvl));
				if (towerLvl == 4) {
					mngr_->setAlive(fenixMoneyText_, false);
					mngr_->setAlive(fenixCoin_, false);
					mngr_->deleteHandler(hdlr_but_id, fenixMoneyText_);
					mngr_->deleteHandler(hdlr_but_id, fenixCoin_);
					std::basic_string s = "LVL: MAX.";
					mngr_->getComponent<TextComponent>(fenixLvlText_)->changeText(s);
					mngr_->getComponent<Transform>(fenixLvlText_)->setScale({ s.size() * font_size.getX(), font_size.getY() });
				}
			}
			break;
		case _twr_SLIME:
			if (towerLvl == 1) {
				if (!mngr_->hasComponent<FramedImage>(slimeImage_))mngr_->addComponent<FramedImage>(slimeImage_, intAt("SlimeColumns"), intAt("SlimeRows"), intAt("SlimeWidth"), intAt("SlimeHeight"), 0, 0);
				mngr_->getComponent<RenderComponent>(slimeImage_)->setTexture(gameTextures::slimeTowerTexture);
			}
			if (towerLvl < 5) {
				towerPriceString = "precioHSlimeLvl" + std::to_string(towerLvl);
				price = intAt(towerPriceString);
				auto fi = mngr_->getComponent<FramedImage>(slimeImage_);
				if (fi != nullptr)
				fi->setCurrentFrame(towerLvl - 1);
				mngr_->getComponent<TextComponent>(slimeMoneyText_)->changeText(std::to_string(price));
				mngr_->getComponent<TextComponent>(slimeLvlText_)->changeText("LVL: " + std::to_string(towerLvl));
				if (towerLvl == 4) {
					mngr_->setAlive(slimeMoneyText_, false);
					mngr_->setAlive(slimeCoin_, false);
					mngr_->deleteHandler(hdlr_but_id, slimeMoneyText_);
					mngr_->deleteHandler(hdlr_but_id, slimeCoin_);
					std::basic_string s = "LVL: MAX.";
					mngr_->getComponent<TextComponent>(slimeLvlText_)->changeText(s);
					mngr_->getComponent<Transform>(slimeLvlText_)->setScale({ s.size() * font_size.getX(), font_size.getY() });
				}
			}
			break;
		case _twr_NEXUS:
			if (towerLvl < 4) {
				towerPriceString = "precioHNexoLvl" + std::to_string(towerLvl);
				price = intAt(towerPriceString);
				mngr_->getComponent<TextComponent>(nexusPriceText_)->changeText(std::to_string(price));
			}else mngr_->getComponent<TextComponent>(nexusPriceText_)->changeText("MAX");
		
		}
	}

	void ButtonSystem::dragTower(twrId tower) {
		if (money_ >= costs[tower]) {
			sdlutils().soundEffects().at("button").play(0, 1);
			Message m;
			m.id = _m_DRAG;
			m.drag_data.towerId = tower;
			mngr_->send(m);
		}
	}
#pragma endregion


Entity* ButtonSystem::addButton(const Vector2D& pos, const Vector2D& scale, gameTextures tex, gameTextures hov, ButtonTypes type,int level, int width, int height, Message m) {
	Entity* b = mngr_->addEntity(_grp_HUD_FOREGROUND);
	mngr_->setHandler(hdlr_but_id, b);

	Transform* tr = mngr_->addComponent<Transform>(b);
	tr->setScale(scale);
	Vector2D aux = tr->getScale();
	tr->setPosition(pos - aux / 2);

	mngr_->addComponent<RenderComponent>(b, tex);

	ButtonComponent* bC = mngr_->addComponent<ButtonComponent>(b, type,m);
	bC->setTexture(tex);
	bC->setHover(hov);
	if (level != 0) {
		bC->setLevel(level);
	}
	else if (width != 0 && height != 0) {
		bC->setHeight(height);
		bC->setWidth(width);
	}
	return b;
}
Entity* ButtonSystem::addSlider(const Vector2D& pos, const Vector2D& scale, gameTextures tex, grpId_type grpId, SliderTypes slTy) {
	Entity* slider = mngr_->addEntity(grpId);
	mngr_->setHandler(hdlr_but_id, slider);
	Transform* tr = mngr_->addComponent<Transform>(slider);
	auto sliderComp = mngr_->addComponent<SliderComponent>(slider, slTy);
	tr->setScale(scale);
	Vector2D aux = tr->getScale();
	
	sliderComp->setRelativeBounds(100,100);
	if (slTy == general) {
		sliderComp->setMax(game().instance()->getNewMaxGeneral());
		sliderComp->setMin(game().instance()->getNewMinGeneral());
	}
	else if (slTy == music) {
		sliderComp->setMax(game().instance()->getNewMaxMusic());
		sliderComp->setMin(game().instance()->getNewMinMusic());
	}
	else if (slTy == effects) {
		sliderComp->setMax(game().instance()->getNewMaxEffects());
		sliderComp->setMin(game().instance()->getNewMinEffects());
	}
	
	float posX = pos.getX() - sliderComp->getRelativeMax() + sliderComp->getMin();
	
	tr->setPosition({ posX - aux.getX() / 2, pos.getY() - aux.getY()/2});
	sliderComp->setBounds(); // Establece los límites del slider
	mngr_->addComponent<RenderComponent>(slider, tex);

	return slider;
}

Entity* ButtonSystem::addImage(const Vector2D& pos, const Vector2D& scale, const double rot, gameTextures t, grpId_type grpId) {
	Entity* img = mngr_->addEntity(grpId);
	mngr_->setHandler(hdlr_but_id, img);
	Transform* tr = mngr_->addComponent<Transform>(img);
	tr->setScale(scale);
	Vector2D aux = tr->getScale();
	tr->setPosition(pos - aux / 2);
	tr->setRotation(rot);
	mngr_->addComponent<RenderComponent>(img, t);
	return img;
}

void ButtonSystem::OnStartGame() {
	moneyText_ = mngr_->addEntity(_grp_TEXTS);
	Transform* tr = mngr_->addComponent<Transform>(moneyText_);
	std::basic_string m_txt = std::to_string(money_);
	Vector2D font_size = { 24.0f, 50.0f };
	tr->setPosition({ 70, 6});
	tr->setScale({ font_size.getX() * m_txt.size(), font_size.getY()});
	mngr_->addComponent<TextComponent>(moneyText_, std::to_string(money_));

	
}

void ButtonSystem::showTempText(string txt, const SDL_Color& color, const Vector2D& pos, const Vector2D& scale, int time)
{
	auto text = mngr_->addEntity(_grp_TEXTS);
	Transform* tr = mngr_->addComponent<Transform>(text);
	tr->setPosition(pos);
	tr->setScale(scale);
	mngr_->addComponent<TextComponent>(text, txt, color);
	mngr_->addComponent<LimitedTime>(text, time);
}

Entity* ButtonSystem::addText(const string& txt, const SDL_Color& color, const Vector2D& pos, const Vector2D& scale, grpId gId)
{
	Entity* text = mngr_->addEntity(gId);
	mngr_->setHandler(hdlr_but_id, text);
	Transform* tr = mngr_->addComponent<Transform>(text);
	tr->setScale(scale);
	Vector2D aux = tr->getScale();
	tr->setPosition(pos - aux / 2);
	mngr_->addComponent<TextComponent>(text, txt, color);
	return text;
}

void ButtonSystem::updateText(int money, const Vector2D& font_size) {
	mngr_->getComponent<TextComponent>(moneyText_)->changeText(std::to_string(money));
	
	auto tr = mngr_->getComponent<Transform>(moneyText_);
	tr->setScale({std::to_string(money).size() * font_size.getX(), font_size.getY()});
}

void ButtonSystem::generateUpgradeImages()
{

	/** --------------------
	*	-- BULLET
	*/
	bulletImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 1 },
		{ towerImagesSize },
		0, gameTextures::bulletTowerTexture, _grp_TOWER_ICONS);
	if(!mngr_->hasComponent<FramedImage>(bulletImage_))mngr_->addComponent<FramedImage>(bulletImage_, intAt("BalasColumns"), intAt("BalasRows"), intAt("BalasWidth"), intAt("BalasHeight"), 0, 0);
	mngr_->getComponent<FramedImage>(bulletImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_BULLET]-1);
	
	/** --------------------
	*	-- CRISTAL
	*/
	if (game().getSaveGame()->getTurretsLevels()[_twr_CRISTAL] == 0) {
		cristalImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 2},
			{ towerImagesSize },
			0, gameTextures::cristal_tower_silueta, _grp_TOWER_ICONS);
	}
	else {
		cristalImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 2 },
			{ towerImagesSize },
			0, gameTextures::cristalTowerTexture, _grp_TOWER_ICONS);
		if (!mngr_->hasComponent<FramedImage>(cristalImage_))mngr_->addComponent<FramedImage>(cristalImage_, intAt("CristalColumns"), intAt("CristalRows"), intAt("CristalWidth"), intAt("CristalHeight"), 0, 0);
		mngr_->getComponent<FramedImage>(cristalImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_CRISTAL]-1);
	}
	
	/** --------------------
	*	-- SLIME
	*/
	if (game().getSaveGame()->getTurretsLevels()[_twr_SLIME] == 0) {
		slimeImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 3 },
			{ towerImagesSize },
			0, gameTextures::slime_tower_silueta, _grp_TOWER_ICONS);
	}
	else {
#ifdef _DEBUG
		std::cout << "SLIME LVL: " << game().getSaveGame()->getTurretsLevels()[_twr_SLIME] << std::endl;
#endif //_DEBUG
		slimeImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 3 },
			{ towerImagesSize },
			0, gameTextures::slimeTowerTexture, _grp_TOWER_ICONS);
		if (!mngr_->hasComponent<FramedImage>(slimeImage_))mngr_->addComponent<FramedImage>(slimeImage_, intAt("SlimeColumns"), intAt("SlimeRows"), intAt("SlimeWidth"), intAt("SlimeHeight"), 0, 0);
		mngr_->getComponent<FramedImage>(slimeImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_SLIME]- 1);
	}

	/** --------------------
	*	-- SNIPER
	*/
	if (game().getSaveGame()->getTurretsLevels()[_twr_DIEGO] == 0) {
		diegoImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 4 },
			{ towerImagesSize },
			0, gameTextures::sniper_tower_silueta, _grp_TOWER_ICONS);
	}
	else {
		diegoImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 4 },
			{ towerImagesSize },
			0, gameTextures::sniperTowerTexture, _grp_TOWER_ICONS);
		if (!mngr_->hasComponent<FramedImage>(diegoImage_))mngr_->addComponent<FramedImage>(diegoImage_, intAt("DiegoSniperColumns"), intAt("DiegoSniperRows"), intAt("DiegoSniperWidth"), intAt("DiegoSniperHeight"), 0, 0);
		mngr_->getComponent<FramedImage>(diegoImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_DIEGO]-1);
	}

	/** --------------------
	*	-- CLAY
	*/
	dirtImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 6 },
		{ towerImagesSize },
		0, gameTextures::clayTowerTexture, _grp_TOWER_ICONS);
	if (!mngr_->hasComponent<FramedImage>(dirtImage_))mngr_->addComponent<FramedImage>(dirtImage_, intAt("ArcillaColumns"), intAt("ArcillaRows"), intAt("ArcillaWidth"), intAt("ArcillaHeight"), 0, 0);
	mngr_->getComponent<FramedImage>(dirtImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_CLAY] - 1);

	/** --------------------
	*	-- ENHANCER
	*/
	if (game().getSaveGame()->getTurretsLevels()[_twr_POWER] == 0) {
		enhancerImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 7 },
			{ towerImagesSize },
			0, gameTextures::booster_tower_silueta, _grp_TOWER_ICONS);
	}
	else {
		enhancerImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 7 },
			{ towerImagesSize },
			0, gameTextures::boosterTowerTexture, _grp_TOWER_ICONS);
		if (!mngr_->hasComponent<FramedImage>(enhancerImage_))mngr_->addComponent<FramedImage>(enhancerImage_, intAt("PotenciadoraColumns"), intAt("PotenciadoraRows"), intAt("PotenciadoraWidth"), intAt("PotenciadoraHeight"), 0, 0);
		mngr_->getComponent<FramedImage>(enhancerImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_POWER] - 1);
	}
	/** --------------------
	*	-- FENIX
	*/
	if (game().getSaveGame()->getTurretsLevels()[_twr_FENIX] == 0) {
		fenixImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) *  5},
			{ towerImagesSize },
			0, gameTextures::phoenix_tower_silueta, _grp_TOWER_ICONS);
	}
	else {
		fenixImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 5 },
			{ towerImagesSize },
			0, gameTextures::phoenixTowerTexture, _grp_TOWER_ICONS);
		if (!mngr_->hasComponent<FramedImage>(fenixImage_))mngr_->addComponent<FramedImage>(fenixImage_, intAt("FenixColumns"), intAt("FenixRows"), intAt("FenixWidth"), intAt("FenixHeight"), 0, 0);
		mngr_->getComponent<FramedImage>(fenixImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_FENIX] - 1);
	}
}

void ButtonSystem::generateHMoneyText() {
	moneyText_ = mngr_->addEntity(_grp_TEXTS);
	Transform* tr = mngr_->addComponent<Transform>(moneyText_);
	basic_string h_money = std::to_string(HMoney_);
	tr->setPosition({ 140,75 });
	tr->setScale({ h_money.size() * font_size_Hcoin_nexus.getX(), font_size_Hcoin_nexus.getY()});
	mngr_->addComponent<TextComponent>(moneyText_, h_money);
}

void ButtonSystem::generateNexusImage(int level, int life) {
	//nexus life text
	nexushealth_ = mngr_->addEntity(_grp_BACKGROUND_TEXTS);
	Transform* textTransform = mngr_->addComponent<Transform>(nexushealth_);
	textTransform->setPosition({ 100.0f, (sdlutils().height() / 2.0f) - 85.0f });
	textTransform->setScale({ 200.0f, 50.0f });
	textTransform->setRotation(0.0f);

	mngr_->addComponent<TextComponent>(nexushealth_, "HEALTH: " + std::to_string(life));
	//Nexus life image
	Vector2D pAux = Vector2D{ 207,500 };
	Vector2D sAux = Vector2D{ 300,100 };
	addImage(pAux, sAux, 0, gameTextures::life, _grp_HUD_FOREGROUND);
	addImage(pAux, sAux, 0, gameTextures::life_background, _grp_HUD_FOREGROUND);
	
	//Nexus image
	nexusImage_ = mngr_->addEntity(_grp_HUD_FOREGROUND);
	Transform* tr = mngr_->addComponent<Transform>(nexusImage_);
	tr->setPosition({ 200,  (sdlutils().height() / 2.0f) - 250.0f });
	Vector2D pos = tr->getPosition();
	mngr_->addComponent<RenderComponent>(nexusImage_, gameTextures::nexusLvl);
	FramedImage* framedImage = mngr_->addComponent<FramedImage>(nexusImage_, 4, 1, 2048, 2048, level - 1, 0, 1);
	tr->setScale({ 350.0f, 350.0f });
	Vector2D aux = tr->getScale();
	tr->setPosition(pos - aux / 2);

}

void ButtonSystem::generateNexusText(int level) {
	nexusLvl_ = mngr_->addEntity(_grp_BACKGROUND_TEXTS);

	Transform* textTransform = mngr_->addComponent<Transform>(nexusLvl_);
	textTransform->setPosition({ 50.0f, (sdlutils().height() / 2.0f) + 50.0f });
	textTransform->setScale({ 300.0f, 75.0f });
	textTransform->setRotation(0.0f);

	mngr_->addComponent<TextComponent>(nexusLvl_, "Nexus Level: " + std::to_string(level));
}

void ButtonSystem::updateNexusImage(int level, int health)
{
	FramedImage* framedImage = mngr_->getComponent<FramedImage>(nexusImage_);
	TextComponent* textComponent = mngr_->getComponent<TextComponent>(nexusLvl_);
	TextComponent* textHealthComponent = mngr_->getComponent<TextComponent>(nexushealth_);
	if (framedImage != nullptr && textComponent != nullptr) {
		framedImage->setCurrentFrame(level - 1);
		string lvl = "Nexus Level: " + std::to_string(level);
		textComponent->changeText(lvl);
		//update nexus life text
		string hlth = "HEALTH: " + std::to_string(health);
		textHealthComponent->changeText(hlth);
	}
}

void ButtonSystem::generateUpgradeMoneyTexts() {
	SDL_Color color = { 255,255,255,255 };

	//NEXUS PRICE TEXT
	int nexusPrice = game().getSaveGame()->getTurretsLevels()[_twr_NEXUS];

	switch (nexusPrice) {
	case 1:
		nexusPrice = intAt("precioHNexoLvl1");
		break;
	case 2:
		nexusPrice = intAt("precioHNexoLvl2");
		break;
	case 3:
		nexusPrice = intAt("precioHNexoLvl3");
		break;

	}
	string nexusText = std::to_string(nexusPrice);
	if (nexusPrice == 4)nexusText = "MAX";

	addImage({ sdlutils().width() - 1040.0f , (sdlutils().height() / 5.5f) * 4.2f }, { 50.0f, 65.0f }, 0.0f, monedaH, _grp_HUD_FOREGROUND);
	nexusPriceText_ = mngr_->addEntity(_grp_BACKGROUND_TEXTS);
	mngr_->setHandler(hdlr_but_id, nexusPriceText_);
	Transform* trnx = mngr_->addComponent<Transform>(nexusPriceText_);
	trnx->setScale({ 50.0f, 65.0f });
	Vector2D auxnx = trnx->getScale();
	trnx->setPosition(Vector2D(sdlutils().width() - 1100.0f, (sdlutils().height() / 1.3f)) - auxnx / 2);
	mngr_->addComponent<TextComponent>(nexusPriceText_, nexusText);

	//BULLET PRICE TEXT
	int bullet_lvl = game().getSaveGame()->getTurretsLevels()[_twr_BULLET];
		int bulletPrice;

	switch (bullet_lvl) {
		case 0:
			bulletPrice = intAt("precioHBalasLvl0");
			break;
		case 1:
			bulletPrice = intAt("precioHBalasLvl1");
			break;
		case 2:
			bulletPrice = intAt("precioHBalasLvl2");
			break;
		case 3:
			bulletPrice = intAt("precioHBalasLvl3");
			break;
		case 4:
			bulletPrice = intAt("precioHBalasLvl4");
			break;
	}
	std::basic_string bullet_txt = "LVL: " + to_string(bullet_lvl);
	if (bullet_lvl == 4) bullet_txt = "LVL: MAX.";
	//Posicion y escala del nivel
	Vector2D bP = Vector2D(sdlutils().width() - lvl_separation, (sdlutils().height() / 5.5f));
	Vector2D bS = Vector2D(bullet_txt.size() * font_size.getX(), font_size.getY());
	//Creamos el texto del nivel
	bulletLvlText_ = addText(bullet_txt, color, bP, bS, _grp_BACKGROUND_TEXTS
	);
	if(bullet_lvl != 4) {
		std::basic_string bulletText = std::to_string(bulletPrice);
		Vector2D bcP = { bP.getX() + bS.getX() / 2 + 35 , bP.getY() };
		//Imagen moneda
		bulletCoin_ = addImage(bcP, { 40.0f, 40.0f }, 0.0f, monedaH, _grp_HUD_FOREGROUND);
		//Texto coste
		Vector2D bmP = { bcP.getX() + 40, bP.getY() };
		Vector2D bmS = { font_size.getX() * bulletText.size(), font_size.getY() };
		bulletMoneyText_ = addText(bulletText, color, bmP, bmS, _grp_BACKGROUND_TEXTS);
	}


	//CRISTAL PRICE TEXT
	int cristalPrice;
	int cristal_lvl = game().getSaveGame()->getTurretsLevels()[_twr_CRISTAL];
	switch (cristal_lvl) {
		case 0:
			cristalPrice = intAt("precioHCristalLvl0");
			break;
		case 1:
			cristalPrice = intAt("precioHCristalLvl1");
			break;
		case 2:
			cristalPrice = intAt("precioHCristalLvl2");
			break;
		case 3:
			cristalPrice = intAt("precioHCristalLvl3");
			break;
		case 4:
			cristalPrice = intAt("precioHCristalLvl4");
			break;
	}
	std::basic_string cristal_txt = "LVL: " + to_string(cristal_lvl);
	if (cristal_lvl == 4)cristal_txt = "LVL: MAX";

	//Posicion y escala del nivel
	Vector2D cP = Vector2D(sdlutils().width() - lvl_separation, (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f) * 1);
	Vector2D cS = Vector2D(cristal_txt.size() * font_size.getX(), font_size.getY());
	//Creamos texto del nivel
	cristalLvlText_ = addText(cristal_txt, color, cP, cS, _grp_BACKGROUND_TEXTS
	);
	if (cristal_lvl != 4) {
		std::basic_string cristalText = std::to_string(cristalPrice);
		Vector2D ccP = { cP.getX() + cS.getX() / 2 + 35 , cP.getY() };
		//Imagen moneda
		cristalCoin_ = addImage(ccP, { 40.0f, 40.0f }, 0.0f, monedaH, _grp_HUD_FOREGROUND);
		//Texto coste
		Vector2D cmP = { ccP.getX() + 40, cP.getY() };
		Vector2D cmS = { font_size.getX() * cristalText.size(), font_size.getY() };
		cristalMoneyText_ = addText(cristalText, color, cmP, cmS, _grp_BACKGROUND_TEXTS);
	}

	//SLIME PRICE TEXT
	int slimePrice;
	int slime_lvl = game().getSaveGame()->getTurretsLevels()[_twr_SLIME];
	switch (slime_lvl) {
		case 0:
			slimePrice = intAt("precioHSlimeLvl0");
			break;
		case 1:
			slimePrice = intAt("precioHSlimeLvl1");
			break;
		case 2:
			slimePrice = intAt("precioHSlimeLvl2");
			break;
		case 3:
			slimePrice = intAt("precioHSlimeLvl3");
			break;
		case 4:
			slimePrice = intAt("precioHSlimeLvl4");
			break;
	}
	
	std::basic_string slime_txt = "LVL: " + to_string(slime_lvl);
	if (slime_lvl == 4)slime_txt = "LVL: MAX";

	//Posicion y escala del nivel
	Vector2D sP = Vector2D(sdlutils().width() - lvl_separation, (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f) * 2);
	Vector2D sS = Vector2D(slime_txt.size() * font_size.getX(), font_size.getY());
	//Creamos texto del nivel
	slimeLvlText_ = addText(slime_txt, color, sP, sS, _grp_BACKGROUND_TEXTS
	);

	if (slime_lvl != 4) {
		std::basic_string slimeText = std::to_string(slimePrice);
		Vector2D scP = { sP.getX() + sS.getX() / 2 + 35 , sP.getY() };
		//Imagen moneda
		slimeCoin_ = addImage(scP, { 40.0f, 40.0f }, 0.0f, monedaH, _grp_HUD_FOREGROUND);
		//Texto coste
		Vector2D smP = { scP.getX() + 40, sP.getY() };
		Vector2D smS = { font_size.getX() * slimeText.size(), font_size.getY() };
		slimeMoneyText_ = addText(slimeText, color, smP, smS, _grp_BACKGROUND_TEXTS);
	}

	//DIEGO PRICE TEXT
	int diegoPrice;
	int diego_lvl = game().getSaveGame()->getTurretsLevels()[_twr_DIEGO];
	switch (diego_lvl) {
		case 0:
			diegoPrice = intAt("precioHDiegoLvl0");
			break;
		case 1:
			diegoPrice = intAt("precioHDiegoLvl1");
			break;
		case 2:
			diegoPrice = intAt("precioHDiegoLvl2");
			break;
		case 3:
			diegoPrice = intAt("precioHDiegoLvl3");
			break;
		case 4:
			diegoPrice = intAt("precioHDiegoLvl4");
			break;
	}
	std::basic_string diego_txt = "LVL: " + to_string(diego_lvl);
	if (diego_lvl == 4)diego_txt = "LVL: MAX";
	//Posicion y escala del nivel
	Vector2D diP = Vector2D(sdlutils().width() - lvl_separation, (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f) * 3);
	Vector2D diS = Vector2D(diego_txt.size() * font_size.getX(), font_size.getY());
	//Creamos texto del nivel
	diegoLvlText_ = addText(diego_txt, color, diP, diS, _grp_BACKGROUND_TEXTS
	);

	if (diego_lvl != 4) {
		std::basic_string diegoText = std::to_string(diegoPrice);
		Vector2D dicP = { diP.getX() + diS.getX() / 2 + 35 , diP.getY() };
		//Imagen moneda
		diegoCoin_ = addImage(dicP, { 40.0f, 40.0f }, 0.0f, monedaH, _grp_HUD_FOREGROUND);
		//Texto coste
		Vector2D dimP = { dicP.getX() + 40, diP.getY() };
		Vector2D dimS = { font_size.getX() * diegoText.size(), font_size.getY() };
		diegoMoneyText_ = addText(diegoText, color, dimP, dimS, _grp_BACKGROUND_TEXTS);
	}
	
	//PHOENIX PRICE TEXT
	int fenixPrice;
	int fenix_lvl = game().getSaveGame()->getTurretsLevels()[_twr_FENIX];
	switch (fenix_lvl) {
		case 0:
			fenixPrice = intAt("precioHFenixLvl0");
			break;
		case 1:
			fenixPrice = intAt("precioHFenixLvl1");
			break;
		case 2:
			fenixPrice = intAt("precioHFenixLvl2");
			break;
		case 3:
			fenixPrice = intAt("precioHFenixLvl3");
			break;
		case 4:
			fenixPrice = intAt("precioHFenixLvl4");
			break;
	}
	std::basic_string fenix_txt = "LVL: " + to_string(fenix_lvl);
	if (fenix_lvl == 4)fenix_txt = "LVL: MAX";

	//Posicion y escala del nivel
	Vector2D fP = Vector2D(sdlutils().width() - lvl_separation, (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f) * 4);
	Vector2D fS = Vector2D(fenix_txt.size() * font_size.getX(), font_size.getY()); 
	//Creamos texto del nivel
	fenixLvlText_ = addText(fenix_txt, color, fP, fS, _grp_BACKGROUND_TEXTS
	);

	if (fenix_lvl != 4){
		std::basic_string fenixText = std::to_string(fenixPrice); 

		Vector2D fcP = { fP.getX() + fS.getX() / 2 + 35 , fP.getY() };
		//Imagen moneda
		fenixCoin_ = addImage(fcP, { 40.0f, 40.0f }, 0.0f, monedaH, _grp_HUD_FOREGROUND); 
		//Texto coste
		Vector2D fmP = { fcP.getX() + 40, fP.getY() }; 
		Vector2D fmS = { font_size.getX() * fenixText.size(), font_size.getY() }; 
		fenixMoneyText_ = addText(fenixText, color, fmP, fmS, _grp_BACKGROUND_TEXTS); 
	}

	//DIRT PRICE TEXT
	int dirtPrice;
	int dirt_lvl = game().getSaveGame()->getTurretsLevels()[_twr_CLAY];
	switch (dirt_lvl) {
		case 0:
			dirtPrice = intAt("precioHArcillaLvl0");
			break;
		case 1:
			dirtPrice = intAt("precioHArcillaLvl1");
			break;
		case 2:
			dirtPrice = intAt("precioHArcillaLvl2");
			break;
		case 3:
			dirtPrice = intAt("precioHArcillaLvl3");
			break;
		case 4:
			dirtPrice = intAt("precioHArcillaLvl4");
			break;

	}
	
	std::basic_string dirt_txt = "LVL: " + to_string(dirt_lvl);
	if (dirt_lvl == 4)dirt_txt = "LVL: MAX";

	//Posicion y escala del nivel
	Vector2D dP = Vector2D(sdlutils().width() - lvl_separation, (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f) * 5);
	Vector2D dS = Vector2D(dirt_txt.size() * font_size.getX(), font_size.getY());
	//Creamos texto del nivel
	dirtLvlText_ = addText(dirt_txt, color, dP, dS, _grp_BACKGROUND_TEXTS
	);

	if (dirt_lvl != 4) {
		std::basic_string dirtText = std::to_string(dirtPrice);
		Vector2D dcP = { dP.getX() + dS.getX() / 2 + 35 , dP.getY() };
		//Imagen moneda
		dirtCoin_ = addImage(dcP, { 40.0f, 40.0f }, 0.0f, monedaH, _grp_HUD_FOREGROUND);
		//Texto coste
		Vector2D dmP = { dcP.getX() + 40, dP.getY() };
		Vector2D dmS = { font_size.getX() * dirtText.size(), font_size.getY() };
		dirtMoneyText_ = addText(dirtText, color,dmP, dmS, _grp_BACKGROUND_TEXTS);
	}



	//ENHANCER PRICE TEXT
	int enhancerPrice;
	int enhancer_lvl = game().getSaveGame()->getTurretsLevels()[_twr_POWER];
	switch (enhancer_lvl) {
	case 0:
		enhancerPrice = intAt("precioHPotenciadoraLvl0");
		break;
	case 1:
		enhancerPrice = intAt("precioHPotenciadoraLvl1");
		break;
	case 2:
		enhancerPrice = intAt("precioHPotenciadoraLvl2");
		break;
	case 3:
		enhancerPrice = intAt("precioHPotenciadoraLvl3");
		break;
	case 4:
		enhancerPrice = intAt("precioHPotenciadoraLvl4");
		break;
	}
	std::basic_string enhancer_txt = "LVL: " + to_string(enhancer_lvl);
	if (enhancer_lvl == 4)
		enhancer_txt= "LVL: MAX";
	//Posicion y escala del nivel
	Vector2D enP = Vector2D(sdlutils().width() - lvl_separation, (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f) * 6);
	Vector2D enS = Vector2D(enhancer_txt.size() * font_size.getX(), font_size.getY());
	//Creamos texto del nivel
	enhancerLvlText_ = addText(enhancer_txt,color, enP, enS, _grp_BACKGROUND_TEXTS
	);

	if (enhancer_lvl != 4) {
		std::basic_string enhancerText = std::to_string(enhancerPrice);
		Vector2D encP = { enP.getX() + enS.getX() / 2 + 35 , enP.getY() };
		//Imagen moneda
		enhancerCoin_ = addImage(encP, { 40.0f, 40.0f }, 0.0f, monedaH, _grp_HUD_FOREGROUND);
		//Texto coste
		Vector2D enmP = {encP.getX() + 40, enP.getY()};
		Vector2D enmS = { font_size.getX() * enhancerText.size(), font_size.getY() };
		enhancerMoneyText_ = addText(enhancerText, color, enmP, enmS, _grp_BACKGROUND_TEXTS);
	}
}

void ButtonSystem::throwUpgradeAnim(const Vector2D& pos) {
		Message m;
		m.id = _m_ANIM_CREATE;
		m.anim_create.idGrp = _grp_HUD_FOREGROUND;
		m.anim_create.animSpeed = 70;
		m.anim_create.iterationsToDelete = 1;
		m.anim_create.pos = pos - Vector2D(130, 30);
		m.anim_create.frameInit = 1;
		m.anim_create.frameEnd = 24;
		m.anim_create.cols = 6;
		m.anim_create.rows = 5;
		m.anim_create.scale = { 160, 160 };
		m.anim_create.width = 273;
		m.anim_create.height = 273;
		m.anim_create.tex = gameTextures::enemy_spawn;
		mngr_->send(m);
}