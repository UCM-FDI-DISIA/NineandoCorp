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
		updateText(money_);
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
		/*--- MEJORAS DEL MENU ---*/
		case upgrade_nexus:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_NEXUS];
			if( lvl < 4)
				upgradeTower(_twr_NEXUS, "precioHNexoLvl" + std::to_string(lvl), bC);
			break;
		case upgrade_crystal_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_CRISTAL];
			if (lvl < towerLevelMax)
				upgradeTower(_twr_CRISTAL, "precioHCristalLvl" + std::to_string(lvl), bC);
			break;
		case upgrade_slime_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_SLIME];
			if (lvl < towerLevelMax)
				upgradeTower(_twr_SLIME, "precioHSlimeLvl" + std::to_string(lvl), bC);
			break;
		case upgrade_bullet_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_BULLET];
			if (lvl < towerLevelMax)
				upgradeTower(_twr_BULLET, "precioHBalasLvl" + std::to_string(lvl), bC);
			break;
		case upgrade_sniper_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_DIEGO];
			if (lvl < towerLevelMax)
				upgradeTower(_twr_DIEGO, "precioHDiegoLvl" + std::to_string(lvl), bC);
			break;
		case upgrade_fenix_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_FENIX];
			if (lvl < towerLevelMax)
				upgradeTower(_twr_FENIX, "precioHFenixLvl" + std::to_string(lvl), bC);
			break;
		case upgrade_clay_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_CLAY];
			if (lvl < towerLevelMax)
				upgradeTower(_twr_CLAY, "precioHArcillaLvl" + std::to_string(lvl), bC);
			break;
		case upgrade_enhancer_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_POWER];
			if (lvl < towerLevelMax)
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
			sdlutils().soundEffects().at("MejoraComprada").play(0, 1);
			setUpgradeTex(bC);
			HMoney_ -= sdlutils().intConst().at(idPrecioJSON);
			updateText(HMoney_);
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
		if (towerLvl < 5) {
			switch (t) {
			case _twr_BULLET:
				towerPriceString = "precioHBalasLvl" + std::to_string(towerLvl);
				price = intAt(towerPriceString);
				mngr_->getComponent<TextComponent>(bulletMoneyText_)->changeText(std::to_string(price));
				mngr_->getComponent<FramedImage>(bulletImage_)->setCurrentFrame(towerLvl - 1);
				break;
			case _twr_CLAY:
				towerPriceString = "precioHArcillaLvl" + std::to_string(towerLvl);
				price = intAt(towerPriceString);
				mngr_->getComponent<TextComponent>(dirtMoneyText_)->changeText(std::to_string(price));
				mngr_->getComponent<FramedImage>(dirtImage_)->setCurrentFrame(towerLvl - 1);
				break;
			case _twr_CRISTAL:
				towerPriceString = "precioHCristalLvl" + std::to_string(towerLvl);
				price = intAt(towerPriceString);
				mngr_->getComponent<TextComponent>(cristalMoneyText_)->changeText(std::to_string(price));
				mngr_->getComponent<FramedImage>(cristalImage_)->setCurrentFrame(towerLvl - 1);
				break;
			case _twr_POWER:
				towerPriceString = "precioHPotenciadoraLvl" + std::to_string(towerLvl);
				price = intAt(towerPriceString);
				mngr_->getComponent<TextComponent>(enhancerMoneyText_)->changeText(std::to_string(price));
				mngr_->getComponent<FramedImage>(enhancerImage_)->setCurrentFrame(towerLvl - 1);
				break;
			case _twr_DIEGO:
				towerPriceString = "precioHDiegoLvl" + std::to_string(towerLvl);
				price = intAt(towerPriceString);
				mngr_->getComponent<TextComponent>(diegoMoneyText_)->changeText(std::to_string(price));
				mngr_->getComponent<FramedImage>(diegoImage_)->setCurrentFrame(towerLvl - 1);
				break;
			case _twr_FENIX:
				towerPriceString = "precioHFenixLvl" + std::to_string(towerLvl);
				price = intAt(towerPriceString);
				mngr_->getComponent<TextComponent>(fenixMoneyText_)->changeText(std::to_string(price));
				mngr_->getComponent<FramedImage>(fenixImage_)->setCurrentFrame(towerLvl - 1);
				break;
			case _twr_SLIME:
				towerPriceString = "precioHSlimeLvl" + std::to_string(towerLvl);
				price = intAt(towerPriceString);
				mngr_->getComponent<TextComponent>(slimeMoneyText_)->changeText(std::to_string(price));
				mngr_->getComponent<FramedImage>(slimeImage_)->setCurrentFrame(towerLvl - 1);
				break;
			case _twr_NEXUS:
				if (towerLvl < 4) {
					towerPriceString = "precioHNexoLvl" + std::to_string(towerLvl);
					price = intAt(towerPriceString);
					mngr_->getComponent<TextComponent>(nexusPriceText_)->changeText(std::to_string(price));
				}else mngr_->getComponent<TextComponent>(nexusPriceText_)->changeText("MAX");
			}
		}
		else {
			switch (t) {
			case _twr_BULLET:
				mngr_->getComponent<TextComponent>(bulletMoneyText_)->changeText("MAX");
				break;
			case _twr_CLAY:
				mngr_->getComponent<TextComponent>(dirtMoneyText_)->changeText("MAX");
				break;
			case _twr_CRISTAL:
				mngr_->getComponent<TextComponent>(cristalMoneyText_)->changeText("MAX");
				break;
			case _twr_POWER:
				mngr_->getComponent<TextComponent>(enhancerMoneyText_)->changeText("MAX");
				break;
			case _twr_DIEGO:
				mngr_->getComponent<TextComponent>(diegoMoneyText_)->changeText("MAX");
				break;
			case _twr_FENIX:
				mngr_->getComponent<TextComponent>(fenixMoneyText_)->changeText("MAX");
				break;
			case _twr_SLIME:
				mngr_->getComponent<TextComponent>(slimeMoneyText_)->changeText("MAX");
				break;

			}
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
	tr->setPosition({ 0,0 });
	tr->setScale({ 150, 50 });
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

Entity* ButtonSystem::addText(const string& txt, const SDL_Color& color, const Vector2D& pos, const Vector2D& scale)
{
	Entity* text = mngr_->addEntity(_grp_TEXTS);
	mngr_->setHandler(hdlr_but_id, text);
	Transform* tr = mngr_->addComponent<Transform>(text);
	tr->setScale(scale);
	Vector2D aux = tr->getScale();
	tr->setPosition(pos - aux / 2);
	mngr_->addComponent<TextComponent>(text, txt, color);
	return text;
}

void ButtonSystem::updateText(int money) {
	mngr_->getComponent<TextComponent>(moneyText_)->changeText(std::to_string(money));
}

void ButtonSystem::generateUpgradeImages()
{
	float twr_img_separation = 325.0f;
	float info_separation = 45.0f;
	Vector2D towerImagesSize{ 80.5f, 112.0f };

	bulletImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 1 },
		{ towerImagesSize },
		0, gameTextures::bulletTowerTexture, _grp_TOWER_ICONS);
	if(!mngr_->hasComponent<FramedImage>(bulletImage_))mngr_->addComponent<FramedImage>(bulletImage_, intAt("BalasColumns"), intAt("BalasRows"), intAt("BalasWidth"), intAt("BalasHeight"), 0, 0);
	mngr_->getComponent<FramedImage>(bulletImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_BULLET]-1);
	if(game().getSaveGame()->getTurretsLevels()[_twr_BULLET] == 5)mngr_->getComponent<FramedImage>(bulletImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_BULLET] - 2);


	cristalImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 2 },
		{ towerImagesSize },
		0, gameTextures::cristalTowerTexture, _grp_TOWER_ICONS);
	if (!mngr_->hasComponent<FramedImage>(cristalImage_))mngr_->addComponent<FramedImage>(cristalImage_, intAt("CristalColumns"), intAt("CristalRows"), intAt("CristalWidth"), intAt("CristalHeight"), 0, 0);
	mngr_->getComponent<FramedImage>(cristalImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_CRISTAL]);
	if (game().getSaveGame()->getTurretsLevels()[_twr_CRISTAL] == 5)mngr_->getComponent<FramedImage>(cristalImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_CRISTAL] - 2);

	slimeImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 3 },
		{ towerImagesSize },
		0, gameTextures::slimeTowerTexture, _grp_TOWER_ICONS);
	if (!mngr_->hasComponent<FramedImage>(slimeImage_))mngr_->addComponent<FramedImage>(slimeImage_, intAt("SlimeColumns"), intAt("SlimeRows"), intAt("SlimeWidth"), intAt("SlimeHeight"), 0, 0);
	mngr_->getComponent<FramedImage>(slimeImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_SLIME]);
	if (game().getSaveGame()->getTurretsLevels()[_twr_SLIME] == 5)mngr_->getComponent<FramedImage>(slimeImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_SLIME] - 2);

	diegoImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 4 },
		{ towerImagesSize },
		0, gameTextures::sniperTowerTexture, _grp_TOWER_ICONS);
	if (!mngr_->hasComponent<FramedImage>(diegoImage_))mngr_->addComponent<FramedImage>(diegoImage_, intAt("DiegoSniperColumns"), intAt("DiegoSniperRows"), intAt("DiegoSniperWidth"), intAt("DiegoSniperHeight"), 0, 0);
	mngr_->getComponent<FramedImage>(diegoImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_DIEGO]);
	if (game().getSaveGame()->getTurretsLevels()[_twr_DIEGO] == 5)mngr_->getComponent<FramedImage>(diegoImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_DIEGO] - 2);

	dirtImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 6 },
		{ towerImagesSize },
		0, gameTextures::clayTowerTexture, _grp_TOWER_ICONS);
	if (!mngr_->hasComponent<FramedImage>(dirtImage_))mngr_->addComponent<FramedImage>(dirtImage_, intAt("ArcillaColumns"), intAt("ArcillaRows"), intAt("ArcillaWidth"), intAt("ArcillaHeight"), 0, 0);
	mngr_->getComponent<FramedImage>(diegoImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_CLAY]);
	if (game().getSaveGame()->getTurretsLevels()[_twr_CLAY] == 5)mngr_->getComponent<FramedImage>(dirtImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_CLAY] - 2);

	enhancerImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 7 },
		{ towerImagesSize },
		0, gameTextures::boosterTowerTexture, _grp_TOWER_ICONS);
	if (!mngr_->hasComponent<FramedImage>(enhancerImage_))mngr_->addComponent<FramedImage>(enhancerImage_, intAt("PotenciadoraColumns"), intAt("PotenciadoraRows"), intAt("PotenciadoraWidth"), intAt("PotenciadoraHeight"), 0, 0);
	mngr_->getComponent<FramedImage>(enhancerImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_POWER]);
	if (game().getSaveGame()->getTurretsLevels()[_twr_POWER] == 5)mngr_->getComponent<FramedImage>(enhancerImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_POWER] - 2);

	fenixImage_ = addImage({ sdlutils().width() - twr_img_separation , (sdlutils().height() / 8.0f) * 5 },
		{ towerImagesSize },
		0, gameTextures::phoenixTowerTexture, _grp_TOWER_ICONS);
	if (!mngr_->hasComponent<FramedImage>(fenixImage_))mngr_->addComponent<FramedImage>(fenixImage_, intAt("FenixColumns"), intAt("FenixRows"), intAt("FenixWidth"), intAt("FenixHeight"), 0, 0);
	mngr_->getComponent<FramedImage>(fenixImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_FENIX]);
	if (game().getSaveGame()->getTurretsLevels()[_twr_FENIX] == 5)mngr_->getComponent<FramedImage>(fenixImage_)->setCurrentFrame(game().getSaveGame()->getTurretsLevels()[_twr_FENIX] - 2);

}

void ButtonSystem::generateHMoneyText() {
	moneyText_ = mngr_->addEntity(_grp_TEXTS);
	Transform* tr = mngr_->addComponent<Transform>(moneyText_);
	tr->setPosition({ 100,75 });
	tr->setScale({ 75, 100 });
	mngr_->addComponent<TextComponent>(moneyText_, std::to_string(HMoney_));
}

void ButtonSystem::generateNexusImage(int level) {

	//Nexus life image
	Vector2D pAux = Vector2D{ 207,500 };
	Vector2D sAux = Vector2D{ 300,100 };
	addImage(pAux, sAux, 0, gameTextures::life, _grp_HUD_FOREGROUND);
	addImage(pAux, sAux, 0, gameTextures::life_background, _grp_HUD_FOREGROUND);

	nexusImage_ = mngr_->addEntity(_grp_HUD_FOREGROUND);
	Transform* tr = mngr_->addComponent<Transform>(nexusImage_);
	tr->setPosition({ 200,  (sdlutils().height() / 2.0f) - 220.0f });
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

void ButtonSystem::updateNexusImage(int level)
{
	FramedImage* framedImage = mngr_->getComponent<FramedImage>(nexusImage_);
	TextComponent* textComponent = mngr_->getComponent<TextComponent>(nexusLvl_);
	if (framedImage != nullptr && textComponent != nullptr) {
		framedImage->setCurrentFrame(level - 1);
		string lvl = "Nexus Level: " + std::to_string(level);
		textComponent->changeText(lvl);
	}
}

void ButtonSystem::generateUpgradeMoneyTexts() {
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
	int bulletPrice = game().getSaveGame()->getTurretsLevels()[_twr_BULLET];

	switch (bulletPrice) {
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
	string bulletText = std::to_string(bulletPrice);
	if (bulletPrice == 5)bulletText = "MAX";

	addImage({ sdlutils().width() - 160.0f , (sdlutils().height() / 5.5f) * 1 }, { 30.0f, 40.0f }, 0.0f, monedaH, _grp_HUD_FOREGROUND);
	bulletMoneyText_ = mngr_->addEntity(_grp_BACKGROUND_TEXTS);
	mngr_->setHandler(hdlr_but_id, bulletMoneyText_);
	Transform* trbt = mngr_->addComponent<Transform>(bulletMoneyText_);
	trbt->setScale({ 30.0f, 45.0f });
	Vector2D auxbt = trbt->getScale();
	trbt->setPosition(Vector2D(sdlutils().width() - 200.0f , (sdlutils().height() / 5.5f)) - auxbt / 2);
	mngr_->addComponent<TextComponent>(bulletMoneyText_, bulletText);;

	//CRISTAL PRICE TEXT
	int cristalPrice = game().getSaveGame()->getTurretsLevels()[_twr_CRISTAL];
	switch (cristalPrice) {
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
	string cristalText = std::to_string(cristalPrice);
	if (cristalPrice == 5)cristalText = "MAX";

	addImage({ sdlutils().width() - 160.0f , (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f) }, { 30.0f, 40.0f }, 0.0f, monedaH, _grp_HUD_FOREGROUND);
	cristalMoneyText_ = mngr_->addEntity(_grp_BACKGROUND_TEXTS);
	mngr_->setHandler(hdlr_but_id, cristalMoneyText_);
	Transform* trc = mngr_->addComponent<Transform>(cristalMoneyText_);
	trc->setScale({ 30.0f, 45.0f });
	Vector2D auxc = trc->getScale();
	trc->setPosition(Vector2D(sdlutils().width() - 190.0f, (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f)) - auxc / 2);
	mngr_->addComponent<TextComponent>(cristalMoneyText_, cristalText);

	//SLIME PRICE TEXT
	int slimePrice = game().getSaveGame()->getTurretsLevels()[_twr_SLIME];
	switch (slimePrice) {
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
	string slimeText = std::to_string(slimePrice);
	if (slimePrice == 5)slimeText = "MAX";

	addImage({ sdlutils().width() - 140.0f , (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f) * 2 }, { 30.0f, 40.0f }, 0.0f, monedaH, _grp_HUD_FOREGROUND);
	slimeMoneyText_ = mngr_->addEntity(_grp_BACKGROUND_TEXTS);
	mngr_->setHandler(hdlr_but_id, slimeMoneyText_);
	Transform* trs = mngr_->addComponent<Transform>(slimeMoneyText_);
	trs->setScale({ 30.0f, 45.0f });
	Vector2D auxs = trs->getScale();
	trs->setPosition(Vector2D(sdlutils().width() - 180.0f, (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f) * 2) - auxs / 2);
	mngr_->addComponent<TextComponent>(slimeMoneyText_, slimeText);

	//DIEGO PRICE TEXT
	int diegoPrice = game().getSaveGame()->getTurretsLevels()[_twr_DIEGO];
	switch (diegoPrice) {
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
	string diegoText = std::to_string(diegoPrice);
	if (diegoPrice == 5)diegoText = "MAX";

	addImage({ sdlutils().width() - 140.0f , (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f) * 3 }, { 30.0f, 40.0f }, 0.0f, monedaH, _grp_HUD_FOREGROUND);
	diegoMoneyText_ = mngr_->addEntity(_grp_BACKGROUND_TEXTS);
	mngr_->setHandler(hdlr_but_id, diegoMoneyText_);
	Transform* trd = mngr_->addComponent<Transform>(diegoMoneyText_);
	trd->setScale({ 30.0f, 45.0f });
	Vector2D auxd = trd->getScale();
	trd->setPosition(Vector2D(sdlutils().width() - 180.0f, (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f) * 3) - auxd / 2);
	mngr_->addComponent<TextComponent>(diegoMoneyText_, diegoText);
	
	//PHOENIX PRICE TEXT
	int fenixPrice = game().getSaveGame()->getTurretsLevels()[_twr_FENIX];
	switch (fenixPrice) {
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
	string fenixText = std::to_string(fenixPrice);
	if (fenixPrice == 5)fenixText = "MAX";

	addImage({ sdlutils().width() - 140.0f , (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f) * 4 }, { 30.0f, 40.0f }, 0.0f, monedaH, _grp_HUD_FOREGROUND);
	fenixMoneyText_ = mngr_->addEntity(_grp_BACKGROUND_TEXTS);
	mngr_->setHandler(hdlr_but_id, fenixMoneyText_);
	Transform* trf = mngr_->addComponent<Transform>(fenixMoneyText_);
	trf->setScale({ 30.0f, 45.0f });
	Vector2D auxf = trf->getScale();
	trf->setPosition(Vector2D(sdlutils().width() - 180.0f, (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f) * 4) - auxf / 2);
	mngr_->addComponent<TextComponent>(fenixMoneyText_, fenixText);

	//DIRT PRICE TEXT
	int dirtPrice = game().getSaveGame()->getTurretsLevels()[_twr_CLAY];
	switch (dirtPrice) {
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
	string dirtText = std::to_string(dirtPrice);
	if (dirtPrice == 5)dirtText = "MAX";

	addImage({ sdlutils().width() - 140.0f , (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f) * 5 }, { 30.0f, 40.0f }, 0.0f, monedaH, _grp_HUD_FOREGROUND);
	dirtMoneyText_ = mngr_->addEntity(_grp_BACKGROUND_TEXTS);
	mngr_->setHandler(hdlr_but_id, dirtMoneyText_);
	Transform* trdrt = mngr_->addComponent<Transform>(dirtMoneyText_);
	trdrt->setScale({ 30.0f, 45.0f });
	Vector2D auxdrt = trdrt->getScale();
	trdrt->setPosition(Vector2D(sdlutils().width() - 180.0f, (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f) * 5) - auxdrt / 2);
	mngr_->addComponent<TextComponent>(dirtMoneyText_, dirtText);



	//ENHANCER PRICE TEXT
	int enhancerPrice = game().getSaveGame()->getTurretsLevels()[_twr_POWER];
	switch (enhancerPrice) {
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
	string enhancerText = std::to_string(enhancerPrice);
	if (enhancerPrice == 5)enhancerText = "MAX";

	addImage({ sdlutils().width() - 140.0f , (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f) * 6 }, { 30.0f, 40.0f }, 0.0f, monedaH, _grp_HUD_FOREGROUND);
	enhancerMoneyText_ = mngr_->addEntity(_grp_BACKGROUND_TEXTS);
	mngr_->setHandler(hdlr_but_id, enhancerMoneyText_);
	Transform* tren = mngr_->addComponent<Transform>(enhancerMoneyText_);
	tren->setScale({ 30.0f, 45.0f });
	Vector2D auxen = tren->getScale();
	tren->setPosition(Vector2D(sdlutils().width() - 180.0f, (sdlutils().height() / 5.5f) + (sdlutils().height() / 8.0f) * 6) - auxen / 2);
	mngr_->addComponent<TextComponent>(enhancerMoneyText_, enhancerText);
}