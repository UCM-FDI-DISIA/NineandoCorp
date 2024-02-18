#include "TowerSystem.h"
#include "../ecs/Manager.h"
#include "../components/AttackComponent.h"

TowerSystem::TowerSystem():elapsedTime_(0), timer_() {
}

TowerSystem::~TowerSystem() {

}

void TowerSystem::initSystem() {
	active_ = true;
}

void TowerSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_ROUND_OVER:
		onRoundOver();
		break;
	}
}


void TowerSystem::update() {
	const auto& towers = mngr_->getEntities(_grp_TOWERS);
	const auto& enemies = mngr_->getEntities(_grp_ENEMIES);

	for (auto& t : towers) {
		AttackComponent* ac = mngr_->getComponent<AttackComponent>(t);
		ac->targetEnemy(enemies);
		elapsedTime_ = timer_.currTime();
		if (elapsedTime_ > ac->getTimeToShoot()) {
			if (ac->shouldShoot()) {
				ac->setLoaded(true);
				if(ac->getTarget() != nullptr) {
					ac->shoot(ac->getTarget());
					ac->setTimeToShoot(ac->getTimeToShoot() + ac->getReloadTime());
					ac->setLoaded(false);
				}
			}
			else {
				ac->setLoaded(true);
				if (ac->getTarget() != nullptr) {
					ac->doDamageTo(mngr_->getComponent<HealthComponent>(ac->getTarget()));
					ac->setTimeToShoot(ac->getTimeToShoot() + ac->getReloadTime());
					ac->setLoaded(false);
				}
			}
		}
		
	}
}

void TowerSystem::onRoundStart() {
	const auto& towers = mngr_->getEntities(_grp_TOWERS);

	for (auto& t : towers) {
		towerTransforms.push_back(mngr_->getComponent<Transform>(t));
	}
}

void TowerSystem::onRoundOver() {
	towerTransforms.clear();
}