#include "MainControlSystem.h"

MainControlSystem::MainControlSystem(int currentLevel) :active_(false), currentLevel(currentLevel)
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
		if(active_)
			currentLevel++;
		game().changeState<MainMenuState>(m.money_data.Hmoney, currentLevel);
		break;
	case _m_LEVEL_SELECTED:
		game().changeState<PlayState>(m.start_game_data.level, turrentLevels_);
		break;
	case _m_LEVEL_SELECTOR:
		game().pushState<LevelSelectorState>(mngr_, currentLevel);
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
	case _m_SAVE_GAME:
		saveGame.setHCoins(m.save_data.Hmoney);
		saveGame.saveFile();
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
			m.id = _m_ROUND_OVER;
			mngr_->send(m);
			active_ = false;
			// Pushear Estado Nuevo?
		}
	}
}

void MainControlSystem::OnStartGame() {

}

void MainControlSystem::onRoundOver() {
	active_ = false;
}

void MainControlSystem::subtractCoins(int num) {
	numDoradasActuales -= num;
}