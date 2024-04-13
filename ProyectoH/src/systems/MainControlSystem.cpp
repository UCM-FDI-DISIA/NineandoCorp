#include "MainControlSystem.h"

MainControlSystem::MainControlSystem(int currentLevel) :nexusIsAlive_(false), currentLevel(currentLevel)
{
	
}

void MainControlSystem::initSystem() {
}

void MainControlSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_START_GAME:
		turrentLevels_ = game().getSaveGame()->getTurretsLevels();
		OnStartGame();
		break;
	case _m_ROUND_OVER:
		if (nexusIsAlive_ && currentLevel == game().getSaveGame()->getLevelsUnlocked()) {
			game().getSaveGame()->setLevelsUnlocked(currentLevel++);
			game().getSaveGame()->saveFile();
		}
		game().changeState<MainMenuState>(m.money_data.money);
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
	case _m_START_MENU:
		turrentLevels_ = game().getSaveGame()->getTurretsLevels();
		break;
	case _m_SAVE_GAME:
		game().getSaveGame()->setHCoins(m.save_data.Hmoney);
		game().getSaveGame()->saveFile();
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
	if (elapsedTime_ > 1.0 && nexusIsAlive_) {
		numDoradasActuales += numDoradasPorSegundo;
		elapsedTime_ = 0;
	}
	if (nexusIsAlive_) {
		// Si la vida del Nexo llega a cero se acaba la partida
		if (mngr_->getComponent<HealthComponent>(nexo)->getHealth() <= 0) {
			Message m;
			m.id = _m_ROUND_OVER;
			mngr_->send(m);
			nexusIsAlive_ = false;
			// Pushear Estado Nuevo?
		}
	}
}

void MainControlSystem::OnStartGame() {

}

void MainControlSystem::onRoundOver() {
	nexusIsAlive_ = false;
}

void MainControlSystem::subtractCoins(int num) {
	numDoradasActuales -= num;
<<<<<<< Updated upstream
=======
}

void MainControlSystem::initializeNexus(gameTextures texture, int life, Vector2D pos){
	nexusIsAlive_ = true;
	nexo = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);
	mngr_->addComponent<NexusComponent>(nexo);
	mngr_->addComponent<RenderComponent>(nexo, texture);
	mngr_->addComponent<HealthComponent>(nexo, life);
	mngr_->addComponent<FramedImage>(nexo, 1, 1, 1011, 673, 1, 1, 1);
	mngr_->addComponent<Transform>(nexo)->setPosition(pos);
	cout << "Nexo: " << texture << life << pos;
>>>>>>> Stashed changes
}