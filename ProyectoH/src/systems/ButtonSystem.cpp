#include "ButtonSystem.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"

ButtonSystem::ButtonSystem(hdlrId_type but_id) : 
	hdlr_but_id(but_id){
}

ButtonSystem::~ButtonSystem(){
}
void ButtonSystem::update () {
	manageButtons();
}


void ButtonSystem::initSystem() {
}
void ButtonSystem::receive(const Message& m){
}


void ButtonSystem::manageButtons() {
	//Posicion actual del mouse
	Vector2D pos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };

	//hover 
	for (auto en : mngr_->getHandler(hdlr_but_id)) {
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
				if (en != nullptr && bC != nullptr) {
					//comprueba la id del button y si no es none llama a la funcion correspondiente
					auto type = bC->isPressed(pos);
					if (type != ButtonTypes::none) callFunction(type, en);
				}
			}
		}
	}
}

#pragma region FUNCIONES DE BOTONES

	//Todas las funciones de los botones del juego
	void ButtonSystem::callFunction(ButtonTypes type, Entity* bC) {
		// Incluye la id del button para incluir 
		switch (type)
		{
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
		case start_game:
			startGame();
			break;

		/*--- MEJORAS DEL MENU ---*/
		case upgrade_nexus:
			break;
		case upgrade_crystal_main:
			break;
		case upgrade_slime_main:
			break;
		case upgrade_bullet_main:
			break;
		case upgrade_sniper_main:
			break;
		case upgrade_fenix_main:
			break;
		case upgrade_clay_main:
			break;
		case upgrade_enhancer_main:
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
		/*----------------------------------------*/
		default:
			break;
		}
	}
	void ButtonSystem::pauseAllButtons() {
		for (auto but : mngr_->getHandler(hdlr_but_id)) {
			auto bC = mngr_->getComponent<ButtonComponent>(but);
			if(bC != nullptr) bC->setActive(false);
		}
	}
	void ButtonSystem::loadLevelSelector() {
		Message m;
		m.id = _m_LEVEL_SELECTOR;
		mngr_->send(m, true);
	}
	void ButtonSystem::Pause() {
		Message m;
		m.id = _m_PAUSE;
		mngr_->send(m, true);
	}
	void ButtonSystem::EnemyBook() {
		Message m;
		m.id = _m_ENEMY_BOOK;
		mngr_->send(m, true);
	}
	void ButtonSystem::backToMainMenu() {
		Message m;
		m.id = _m_BACK_TO_MAINMENU;
		mngr_->send(m);
	}
	void ButtonSystem::startGame() {
		Message m;
		m.id = _m_START_GAME;
		mngr_->send(m);
	}
	void ButtonSystem::upgradeNexusMain() {
		upgradeTower(_twr_NEXUS);
	}
	void ButtonSystem::upgradeCrystalMain() {
		upgradeTower(_twr_CRISTAL);
	}
	void ButtonSystem::upgradeSlimeMain() {
		upgradeTower(_twr_SLIME);
	}
	void ButtonSystem::upgradeBulletMain() {
		upgradeTower(_twr_BULLET);
	}
	void ButtonSystem::upgradeSniperMain() {
		upgradeTower(_twr_DIEGO);
	}
	void ButtonSystem::upgradeFenixMain() {
		upgradeTower(_twr_FENIX);
	}
	void ButtonSystem::upgradeClayMain() {
		upgradeTower(_twr_CLAY);
	}
	void ButtonSystem::upgradeEnhancerMain() {
		upgradeTower(_twr_POWER);
	}

	void ButtonSystem::upgradeTower(twrId t) {
		Message m;
		m.id = _m_UPGRADE_TOWER;
		m.drag_data.towerId = t;
		mngr_->send(m);
	}

	void ButtonSystem::dragTower(twrId tower) {
		
	}
#pragma endregion


Entity* ButtonSystem::addButton(const Vector2D& pos, const Vector2D& scale, gameTextures tex, gameTextures hov, ButtonTypes type) {
	Entity* b = mngr_->addEntity(_grp_HUD_FOREGROUND);
	mngr_->setHandler(hdlr_but_id, b);

	Transform* tr = mngr_->addComponent<Transform>(b);
	tr->setScale(scale);
	Vector2D aux = tr->getScale();
	tr->setPosition(pos - aux / 2);

	mngr_->addComponent<RenderComponent>(b, tex);

	ButtonComponent* bC = mngr_->addComponent<ButtonComponent>(b, type);
	bC->setTexture(tex);
	bC->setHover(hov);
	return b;
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
