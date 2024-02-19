#include "TowerSystem.h"
#include "../ecs/Manager.h"
#include "../components/AttackComponent.h"
#include "../components/BulletTower.h"

TowerSystem::TowerSystem() {
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
	const auto& bullets = mngr_->getEntities(_grp_BULLETS);

	for (auto& t : towers) {
		AttackComponent* ac = mngr_->getComponent<AttackComponent>(t);
		if (ac != nullptr) {
			ac->targetEnemy(enemies);
			//ac->setElapsedTime(timer_.currTime());
			if (ac->getElapsedTime() > ac->getTimeToShoot()) {
				ac->setLoaded(true);
				if (ac->getTarget() != nullptr) {
					ac->shoot(ac->getTarget());
					ac->setTimeToShoot(ac->getTimeToShoot() + ac->getReloadTime());
					ac->setLoaded(false);
				}		
			}
		}
		BulletTower* bt = mngr_->getComponent<BulletTower>(t);
		
		if (bt != nullptr) {

		}
	}

	for (auto& b : bullets) {
		Transform* t = mngr_->getComponent<Transform>(b);
		BulletComponent* bc = mngr_->getComponent<BulletComponent>(b);

		t->translate();
		if (!mngr_->isAlive(bc->getTarget())) {//Si ha muerto por el camino
			bc->onTravelEnds();
		}
		else if ((*(t->getPosition()) - *(mngr_->getComponent<Transform>(bc->getTarget())->getPosition())).magnitude() <= 0.1f) {//Si choca con el enemigo
			bc->doDamageTo(mngr_->getComponent<HealthComponent>(bc->getTarget()));
			bc->onTravelEnds();
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