#include "MainControlSystem.h"

MainControlSystem::MainControlSystem() :active_(false)
{
	
}

void MainControlSystem::initSystem() {

	// Tamaño al array
	levels_.resize(8);
	// Inicialización del nivel de las torres y nexo
	for (int i = 0; i < levels_.size(); i++) {
		levels_[i] = 0;
	}
}

void MainControlSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_START_GAME:

		game().changeState<PlayState>();
		break;
	case _m_LEVEL_SELECTOR:
		game().pushState<LevelSelectorState>(mngr_);
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
	}
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
