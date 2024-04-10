#include "MainControlSystem.h"

MainControlSystem::MainControlSystem() :active_(false)
{
	
}

void MainControlSystem::initSystem() {
	// Inicializaci�n del nivel de las torres y nexo
	for (int i = 0; i < _twr_SIZE; i++) {
		turrentLevels_[i] = 0;
	}
}

void MainControlSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_START_GAME:
		OnStartGame();
		break;
	case _m_ROUND_OVER:
		game().changeState<MainMenuState>(m.money_data.Hmoney);
		break;
	case _m_LEVEL_SELECTED:
		game().changeState<PlayState>(m.start_game_data.level);
		break;
	case _m_LEVEL_SELECTOR:
		game().pushState<LevelSelectorState>(mngr_);
		break;
	case _m_ENEMY_BOOK:
		game().pushState<EnemyBookState>(mngr_);
		break;
	case _m_BACK_TO_MAINMENU:
		game().popState();
		resetButtons();
		break;
	case _m_PAUSE:
		game().pushState<PauseState>(mngr_);
		break;
	case _m_ATTACK_NEXUS:		
		mngr_->getComponent<HealthComponent>(nexo)->subtractHealth(m.nexus_attack_data.damage);
		break;
	case _m_UPGRADE_TOWER:
		upgradeTower(m.upgrade_tower.towerId);
		break;
	case _m_SHOW_UPGRADE_TOWER_MENU:
		//std::cout << "ID de torre: " << m.show_upgrade_twr_menu_data.tId << std::endl;
		break;
	}
}

void MainControlSystem::upgradeTower(twrId id) {
	if (turrentLevels_[id] < 4) {
		turrentLevels_[id]++;
		std::cout << turrentLevels_[id] << endl;	// QUITAR
	}
	else {
		std::cout << "NO SE PUEDE MEJORAR, lvl: " << turrentLevels_[id] << endl;	// QUITAR
	}
}

void MainControlSystem::update() {
	elapsedTime_ += game().getDeltaTime();
	if (elapsedTime_ > 1.0 && active_) {
		numDoradasActuales += numDoradasPorSegundo;
		elapsedTime_ = 0;
	}
	if (active_) {
		// Si la vida del Nexo llega a cero se acaba la partida
		if (mngr_->getComponent<HealthComponent>(nexo)->getHealth() <= 0) {
			Message m;
			m.id = _m_OVER_GAME;
			mngr_->send(m);
			// Pushear Estado Nuevo?
		}
	}
}

void MainControlSystem::OnStartGame() {

	// Initializaci�n del Nexo
	string nexusTextureName = "nexusLvl" + turrentLevels_[_twr_NEXUS];
	initializeNexus(nexusLvl1, 1000.0f, { 580.0f, 980.0f });		// Editar para usar NexusTextureName
	cout << "ronda1 empieza";
}

void MainControlSystem::onRoundOver() {
	active_ = false;
}

void MainControlSystem::subtractCoins(int num) {
	numDoradasActuales -= num;
}

void MainControlSystem::initializeNexus(gameTextures texture, int life, Vector2D pos){
	active_ = true;
	nexo = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);
	mngr_->addComponent<NexusComponent>(nexo);
	mngr_->addComponent<RenderComponent>(nexo, texture);
	mngr_->addComponent<HealthComponent>(nexo, life);
	mngr_->addComponent<FramedImage>(nexo, 1, 1, 1011, 673, 1, 1, 1);
	mngr_->addComponent<Transform>(nexo)->setPosition(pos);
	cout << "Nexo: " << texture << life << pos;
}