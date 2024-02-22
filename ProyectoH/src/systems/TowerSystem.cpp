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
	const auto& bullets = mngr_->getEntities(_grp_BULLETS);

	for (auto& t : towers) {
		AttackComponent* ac = mngr_->getComponent<AttackComponent>(t);
		if (ac != nullptr) {		
			ac->setElapsedTime(timer_.currTime()/1000);
			if (ac->getElapsedTime() > ac->getTimeToShoot()) {
				ac->setLoaded(true);
				ac->targetEnemy(enemies);
					//std::cout <<  "Elapsed: " << timer_.currTime() << "\n";
					//std::cout << "TTS: " << ac->getTimeToShoot() << "\n";Per o
				if (ac->getTarget() != nullptr) {
					shootBullet(ac->getTarget(), ac->getDamage());
					ac->setTimeToShoot(ac->getTimeToShoot() + ac->getReloadTime());
					ac->setLoaded(false);
				}		
			}
		}
		BulletTower* bt = mngr_->getComponent<BulletTower>(t);	
		if (bt != nullptr && bt->isMaxLevel()) {
			bt->setElapsedTime(timer_.currTime() / 1000);
			if (bt->getElapsedTime() > bt->getTimeToShoot()) {
				bt->targetSecondEnemy(enemies);
				if (bt->getTarget() != nullptr) { shootBullet(bt->getTarget(), bt->getDamage()); }
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
		else{ //Si choca con el enemigo
			if (((*(t->getPosition()) - *(mngr_->getComponent<Transform>(bc->getTarget())->getPosition())).magnitude() <= 5.0f)) {
				bc->doDamageTo(mngr_->getComponent<HealthComponent>(bc->getTarget()));
				bc->onTravelEnds();
			}
		}
	}
}

void TowerSystem::shootBullet(Entity* target, float damage) {
	Entity* bullet = mngr_->addEntity(_grp_BULLETS);
	Transform* t = mngr_->addComponent<Transform>(bullet);
	mngr_->addComponent<BulletComponent>(bullet, t, target, damage);
	mngr_->addComponent<RenderComponent>(bullet, square);
}

void TowerSystem::addTower() {
	Entity* t = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);
	towers.push_back(t);
}

void TowerSystem::onRoundStart() {
	
}

void TowerSystem::onRoundOver() {
	
}