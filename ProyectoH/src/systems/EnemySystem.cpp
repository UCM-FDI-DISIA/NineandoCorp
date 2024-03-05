#include "EnemySystem.h"
#include "..//components/MovementComponent.h"
#include "..//components/RouteComponent.h"
#include "..//components/HealthComponent.h"
#include "../ecs/Manager.h"

EnemySystem::EnemySystem() {

}
EnemySystem::~EnemySystem() {

}


void EnemySystem::initSystem() {
	active_ = true;

	Entity* enemie = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);
	Transform* tr = mngr_->addComponent<Transform>(enemie);
	tr->setPosition({(float)sdlutils().width()/2.f - 100.f, 300.f});
	tr->setVelocity({ 0, 20 });
	mngr_->addComponent<MovementComponent>(enemie);
	std::vector<Vector2D> route;
	route.push_back({ (float)sdlutils().width() / 2.f, 300.f });
	route.push_back({ (float)sdlutils().width() / 2.f, 600.f });
	mngr_->addComponent<RouteComponent>(enemie, route);
	mngr_->addComponent<AttackComponent>(enemie, 100, 0.25, 20, false);
	mngr_->addComponent<RenderComponent>(enemie, square);
	mngr_->addComponent<HealthComponent>(enemie, 100);
	mngr_->setHandler(_hdlr_ENEMIES, enemie);
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
		if (mngr_->isAlive(m.entity_to_attack.e)) {
			 HealthComponent* h = mngr_->getComponent<HealthComponent>(m.entity_to_attack.e);
			 if (h->getHealth() - m.entity_to_attack.damage <= 0) { mngr_->deleteHandler(_hdlr_ENEMIES, m.entity_to_attack.e); }
			 h->subtractHealth(m.entity_to_attack.damage);
		}		
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
		//std::cout << enemies.size();
		RouteComponent* rc = mngr_->getComponent<RouteComponent>(e);
		MovementComponent* mc = mngr_->getComponent<MovementComponent>(e);
		AttackComponent* ac = mngr_->getComponent<AttackComponent>(e);

		/*if (rc != nullptr) {
			rc->checkdestiny();
			if (mc != nullptr && !mc->getStop()) {
				mc->Move();
			}

		}*/
		if (ac != nullptr) {
			ac->setElapsedTime(game().getDeltaTime());
			if (ac->getElapsedTime() > ac->getTimeToShoot() * 1000) {
				ac->setLoaded(true);
				ac->targetEnemy(towers);

				if (ac->getTarget() != nullptr && mngr_->isAlive(ac->getTarget())) {
					ac->doDamageTo(ac->getTarget(), ac->getDamage());
					ac->setTimeToShoot(ac->getTimeToShoot() + ac->getReloadTime());
					ac->setLoaded(false);
				}
			}
		}

	}
}