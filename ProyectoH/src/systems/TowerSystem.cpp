#include "TowerSystem.h"


TowerSystem::TowerSystem() :timer_(), active_(true) {
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
			ac->setElapsedTime(timer_.currTime());
			if (ac->getElapsedTime() > ac->getTimeToShoot()) {
				ac->setLoaded(true);
				ac->targetEnemy(enemies);
				if (ac->getTarget() != nullptr) {
					ac->shoot(ac->getTarget());
					ac->setTimeToShoot(ac->getTimeToShoot() + ac->getReloadTime());
					ac->setLoaded(false);
				}		
			}
		}
		BulletTower* bt = mngr_->getComponent<BulletTower>(t);	
		if (bt != nullptr) {
			if (bt->getElapsedTime() > bt->getTimeToShoot() && bt->isMaxLevel()) {
				bt->targetSecondEnemy(enemies);
				if (bt->getTarget() != nullptr) { bt->shoot(bt->getTarget()); }
				bt->setElapsedTime(0);
			}
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
	for (auto& t : mngr_->getEntities(_grp_TOWERS)) {
		towerTransforms.push_back(mngr_->getComponent<Transform>(t));
	}
}

void TowerSystem::onRoundOver() {
	towerTransforms.clear();
}