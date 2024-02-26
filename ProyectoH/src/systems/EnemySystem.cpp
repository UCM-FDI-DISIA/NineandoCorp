#include "EnemySystem.h"
#include "..//components/MovementComponent.h"
#include "..//components/RouteComponent.h"
#include "../ecs/Manager.h"

EnemySystem::EnemySystem() {

}
EnemySystem::~EnemySystem() {

}


void EnemySystem::initSystem() {
	active_ = true;
}
void  EnemySystem::receive(const Message& m) {
	switch (m.id) {
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_ROUND_OVER:
		onRoundOver();
		break;
	case _m_ENTITY_TO_ATTACK:
		mngr_->getComponent<HealthComponent>(m.entity_to_attack.e)->subtractHealth(m.entity_to_attack.damage);
		break;
	}

}
void EnemySystem::onRoundStart() {
	const auto& enemies = mngr_->getHandler(_hdlr_ENEMIES);

	for (auto& t : enemies) {
		enemiesTransforms.push_back(mngr_->getComponent<Transform>(t));
	}
}

void EnemySystem::onRoundOver() {
	enemiesTransforms.clear();
}
void EnemySystem::update() {
	const auto& enemies = mngr_->getHandler(_hdlr_ENEMIES);
	const auto& towers = mngr_->getHandler(_hdlr_LOW_TOWERS);
	for (auto& e : enemies) {
		RouteComponent* rc = mngr_->getComponent<RouteComponent>(e);
		MovementComponent* mc = mngr_->getComponent<MovementComponent>(e);
		AttackComponent* ac = mngr_->getComponent<AttackComponent>(e);

		if (rc != nullptr) {
			rc->checkdestiny();
			if (mc != nullptr && !mc->getStop()) {
				mc->Move();
			}

		}
		if (ac != nullptr) {
			ac->setElapsedTime(timer_.currTime() / 1000);
			if (ac->getElapsedTime() > ac->getTimeToShoot()) {
				ac->setLoaded(true);
				ac->targetEnemy(mngr_->getHandler(_hdlr_ENEMIES));

				if (ac->getTarget() != nullptr) {
					ac->doDamageTo(ac->getTarget(), ac->getDamage());
					ac->setTimeToShoot(ac->getTimeToShoot() + ac->getReloadTime());
					ac->setLoaded(false);
				}
		
		}

	}
}