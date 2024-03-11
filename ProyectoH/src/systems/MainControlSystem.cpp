#include "MainControlSystem.h"

MainControlSystem::MainControlSystem() :active_(false)
{
	
}

void MainControlSystem::initSystem() {

	// Tama�o al array de torres
	turrentLevels_.resize(7);

	// Inicializaci�n del nivel de las torres y nexo
	for (int i = 0; i < turrentLevels_.size(); i++) {
		turrentLevels_[i] = 0;
	}

	int nexusLevel_ = 0;
}

void MainControlSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_START_GAME:

		game().changeState<PlayState>();
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
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_ROUND_OVER:
		onRoundOver();
		break;
	case _m_SHIELD_NEXUS:
		mngr_->getComponent<NexusComponent>(nexo)->activateShield();
		mngr_->getComponent<NexusComponent>(nexo)->setShieldHitpoints(m.shield_data.shield);
		break;
	case _m_ATTACK_NEXUS:
		if (mngr_->getComponent<NexusComponent>(nexo)->isShieldActive()) {
			mngr_->getComponent<NexusComponent>(nexo)->setShieldHitpoints(mngr_->getComponent<NexusComponent>(nexo)->getShieldHitpoints() - m.nexus_attack_data.damage);

		}
		else mngr_->getComponent<HealthComponent>(nexo)->subtractHealth(m.nexus_attack_data.damage);
		break;
	case _m_UPGRADE_NEXUS:
		upgradeNexus();
		break;
	case _m_UPGRADE_TOWER:
		upgradeTower(m.upgrade_tower.towerId);
		break;
	case _m_LEVELS_INFO:
		// Creo que esto no hace falta usarlo al final
		break;
	}
}

void MainControlSystem::upgradeNexus() {
	nexusLevel_++;
}

void MainControlSystem::upgradeTower(twrId_type id) {
	turrentLevels_[id]++;
}

void MainControlSystem::update() {
	elapsedTime_ += game().getDeltaTime();
	if (elapsedTime_ > 1.0 && active_) {
		numDoradasActuales += numDoradasPorSegundo;
		elapsedTime_ = 0;
	}
	if (active_) {
		if(mngr_->getComponent<NexusComponent>(nexo)->getShieldHitpoints() <= 0)mngr_->getComponent<NexusComponent>(nexo)->inactivateShield();

		//std::cout << mngr_->getComponent<NexusComponent>(nexo)->getShieldHitpoints() << "\n";
	}
}

void MainControlSystem::onRoundStart() {
	active_ = true;
	nexo = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);
	mngr_->addComponent<NexusComponent>(nexo);
	mngr_->addComponent<RenderComponent>(nexo, nexusTexture);
	mngr_->addComponent<HealthComponent>(nexo, 1000.0f);
	mngr_->addComponent<Transform>(nexo)->setPosition({ 800.0f, 800.0f });
}

void MainControlSystem::onRoundOver() {
	active_ = false;
}

void MainControlSystem::subtractCoins(int num) {
	numDoradasActuales -= num;
}
