#include "ButtonSystem.h"
#include "../game/Game.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"
#include "../components/TextComponent.h"
#include "../components/FramedImage.h"
#include "../components/LimitedTime.h"

ButtonSystem::ButtonSystem(hdlrId_type but_id) : 
	hdlr_but_id(but_id), money_(0), HMoney_(0){
	mActive = true;
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
	case _m_SELL_TOWER:
		money_ += m.sell_tower_data.money;
		updateText(money_);
		break;
	case _m_START_MENU:
		HMoney_ = m.money_data.money;
		game().getSaveGame()->setHCoins(HMoney_);
		generateHMoneyText();
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
	case _m_PAUSE:
		mActive = !m.start_pause.onPause;
		break;
	default:
		break;
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
			sdlutils().soundEffects().at("button").play(0,1);
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
						cout << volume << endl;
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

	//Todas las funciones de los botones del juego
	void ButtonSystem::callFunction(ButtonTypes type, Entity* bC) {
		// Incluye la id del button para incluir 
		int lvl;
		switch (type)
		{
		case back_to_menu:
			game().changeState<MainMenuState>();
			break;
		case exit_button:
			game().exitGame();
			break;
		case selector_main:
			loadLevelSelector();
			pauseAllButtons();
			break;
		case enemies_main:
			EnemyBook();
			pauseAllButtons();
			break;
		case back_selector:
			backToMainMenu();
			break;
		case config:
			Config();
			break;
		case level_selected:
			startGame(bC);
			break;
		case play_wave:
			startWave();
			break;
		case pause_main:
			Pause(true);
			break;
		case resume_main:
			game().popState();
			Pause(false);
			break;
		case enemybook:
			mngr_->send(mngr_->getComponent<ButtonComponent>(bC)->getMessage());			
			break;
		/*--- MEJORAS DEL MENU ---*/
		case upgrade_nexus:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_NEXUS];
			if( lvl < towerLevelMax)
				upgradeTower(_twr_NEXUS, "precioHNexoLvl" + std::to_string(lvl));
			break;
		case upgrade_crystal_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_CRISTAL];
			if (lvl < towerLevelMax)
				upgradeTower(_twr_CRISTAL, "precioHCristalLvl" + std::to_string(lvl));
			break;
		case upgrade_slime_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_SLIME];
			if (lvl < towerLevelMax)
				upgradeTower(_twr_SLIME, "precioHSlimeLvl" + std::to_string(lvl));
			break;
		case upgrade_bullet_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_BULLET];
			if (lvl < towerLevelMax)
				upgradeTower(_twr_BULLET, "precioHBalasLvl" + std::to_string(lvl));
			break;
		case upgrade_sniper_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_DIEGO];
			if (lvl < towerLevelMax)
				upgradeTower(_twr_DIEGO, "precioHDiegoLvl" + std::to_string(lvl));
			break;
		case upgrade_fenix_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_FENIX];
			if (lvl < towerLevelMax)
				upgradeTower(_twr_FENIX, "precioHFenixLvl" + std::to_string(lvl));
			break;
		case upgrade_clay_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_CLAY];
			if (lvl < towerLevelMax)
				upgradeTower(_twr_CLAY, "precioHArcillaLvl" + std::to_string(lvl));
			break;
		case upgrade_enhancer_main:
			lvl = game().getSaveGame()->getTurretsLevels()[_twr_POWER];
			if (lvl < towerLevelMax)
				upgradeTower(_twr_POWER, "precioHPotenciadoraLvl" + std::to_string(lvl));
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
			mngr_->send(mngr_->getComponent<ButtonComponent>(bC)->getMessage());
			break;

		/*--- UPGRADE TOWER ---*/
		case upgrade_tower: 
			mngr_->send(mngr_->getComponent<ButtonComponent>(bC)->getMessage());
			break;
		case exit_up_menu:
			exitUpMenu();
			break;
		/*----------------------------------------*/
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
	void ButtonSystem::Config() {
		mngr_->getComponent<TextComponent>(moneyText_)->isActive = false;
		Message m;
		m.id = _m_CONFIG;
		mngr_->send(m, true);
	}
	void ButtonSystem::EnemyBook() {
		Message m;
		m.id = _m_ENEMY_BOOK;
		mngr_->send(m, true);
	}
	void ButtonSystem::backToMainMenu() {
		mngr_->getComponent<TextComponent>(moneyText_)->isActive = true;
		Message m;
		m.id = _m_BACK_TO_MAINMENU;
		mngr_->send(m);
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
	void ButtonSystem::upgradeTower(twrId t, string idPrecioJSON) {
		if (HMoney_ - sdlutils().intConst().at(idPrecioJSON) >= 0) {
			HMoney_ -= sdlutils().intConst().at(idPrecioJSON);
			updateText(HMoney_);
			game().getSaveGame()->setHCoins(HMoney_);
			Message m;
			m.id = _m_UPGRADE_TOWER;
			m.upgrade_tower.towerId = t;
			mngr_->send(m);
		}
	}

	void ButtonSystem::dragTower(twrId tower) {
		if (money_ >= costs[tower]) {
			Message m;
			m.id = _m_DRAG;
			m.drag_data.towerId = tower;
			mngr_->send(m);
		}
	}
#pragma endregion


Entity* ButtonSystem::addButton(const Vector2D& pos, const Vector2D& scale, gameTextures tex, gameTextures hov, ButtonTypes type,int level, Message m) {
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
	return b;
}
Entity* ButtonSystem::addSlider(const Vector2D& pos, const Vector2D& scale, gameTextures tex, grpId_type grpId) {
	Entity* slider = mngr_->addEntity(grpId);
	mngr_->setHandler(hdlr_but_id, slider);
	Transform* tr = mngr_->addComponent<Transform>(slider);
	tr->setScale(scale);
	Vector2D aux = tr->getScale();
	tr->setPosition(pos - aux / 2);

	mngr_->addComponent<RenderComponent>(slider, tex);
	auto sliderComp = mngr_->addComponent<SliderComponent>(slider);
	sliderComp->setBounds(); // Establece los límites del slider
	sliderComp->setRelativeBounds(100);
	//sliderComp->setOnChangeCallback([](float value) {
	//	// Lógica para manejar el cambio de valor del slider
	//	});

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

void ButtonSystem::generateHMoneyText() {
	moneyText_ = mngr_->addEntity(_grp_TEXTS);
	Transform* tr = mngr_->addComponent<Transform>(moneyText_);
	tr->setPosition({ 100,75 });
	tr->setScale({ 75, 100 });
	mngr_->addComponent<TextComponent>(moneyText_, std::to_string(HMoney_));
}
