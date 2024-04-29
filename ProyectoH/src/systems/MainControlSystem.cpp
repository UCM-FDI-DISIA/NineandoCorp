#include "MainControlSystem.h"

MainControlSystem::MainControlSystem(int currentLevel) :nexusIsAlive_(false),isPlaying(false), currentLevel(currentLevel)
{
	std::fill_n(enemiesSaw, _enm_SIZE, false);
}

void MainControlSystem::initSystem() {
}

void MainControlSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_START_GAME:
		nexusIsAlive_ = true;
		isPlaying = true;
		OnStartGame();
		break;
	case _m_ROUND_OVER:
		onGameOver();
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
	case _m_ENEMY_DIED:
		enemiesDefeated++;
		break;
	case _m_ENEMYSEE:
		enemiesSaw[m.start_enemy_book.n] = true;
		break;
	case _m_CONFIG:
		game().pushState<ConfigState>(mngr_, isPlaying);
		break;
	case _m_BACK_TO_MAINMENU:
		game().SetDelay(1.0f);
		game().popState();
		resetButtons();
		break;
	case _m_ADD_MONEY_H:
		coinsH += m.money_data.money;
		break;
	case _m_PAUSE:
		game().pushState<PauseState>(mngr_);
		break;
	case _m_ACELERATE:
		game().SetDelay(m.acelerate_plus.acel);
		break;
	case _m_ATTACK_NEXUS:		
		
			nexusIsAlive_ = false;
			onGameOver();
		
		break;
	case _m_UPGRADE_TOWER:
		upgradeTower(m.upgrade_tower.towerId);
		break;
	case _m_SHOW_UPGRADE_TOWER_MENU:
		//std::cout << "ID de torre: " << m.show_upgrade_twr_menu_data.tId << std::endl;
		break;
	case _m_START_MENU:
		turrentLevels_ = game().getSaveGame()->getTurretsLevels();
		isPlaying = false;
		break;
	case _m_WAVE_START:
		if (m.start_wave.play) {
			round++;
			Message m1;
			m1.id = _m_ADD_TEXT;
			m1.add_text_data.txt = "Wave: " + to_string((int)round);
			m1.add_text_data.color = { 255, 255 ,255, 255 };
			Vector2D txtScale = Vector2D(200.0f, 60.0f);
			m1.add_text_data.pos = Vector2D(sdlutils().width() / 2, 50.0) - (txtScale / 2);
			m1.add_text_data.scale = txtScale;
			m1.add_text_data.time = 3;
			mngr_->send(m1);
		}
		break;
	}
}

void MainControlSystem::upgradeTower(twrId id) {
	turrentLevels_[id]++;
	game().getSaveGame()->saveFile();

	Message m2;
	m2.id = _m_UPDATE_MENU;
	mngr_->send(m2);
}

void MainControlSystem::update() {
	elapsedTime_ += game().getDeltaTime();
	if (elapsedTime_ > 1.0 && nexusIsAlive_) {
		Message m;
		m.id = _m_ADD_MONEY;
		m.money_data.money = numDoradasPorSegundo;
		elapsedTime_ = 0;
		mngr_->send(m);		// Faltaba enviar el mensaje
	}
}

void MainControlSystem::onGameOver() {
		if (nexusIsAlive_ && currentLevel == game().getSaveGame()->getLevelsUnlocked()) {
			game().getSaveGame()->setLevelsUnlocked(currentLevel+1);
		}
		game().getSaveGame()->addHCoins(coinsH);
		game().getSaveGame()->checkEnemies(enemiesSaw);
		game().getSaveGame()->saveFile();
		game().changeState<GameOverState>(round, enemiesDefeated, coinsH, currentLevel, nexusIsAlive_);
}

void MainControlSystem::OnStartGame() {

}