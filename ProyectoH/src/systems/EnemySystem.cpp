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
	}
}
void EnemySystem::onRoundStart() {
	const auto& towers = mngr_->getEntities(_grp_ENEMIES);

	for (auto& t : towers) {
		enemiesTransforms.push_back(mngr_->getComponent<Transform>(t));
	}
}

void EnemySystem::onRoundOver() {
	enemiesTransforms.clear();
}
void EnemySystem::update() {
	const auto& enemies = mngr_->getEntities(_grp_ENEMIES);
	const auto& towers = mngr_->getEntities(_grp_TOWERS);
	for (auto& e : enemies) {
		RouteComponent* rc = mngr_->getComponent<RouteComponent>(e);
		MovementComponent* mc = mngr_->getComponent<MovementComponent>(e);
		if (rc != nullptr) {
			rc->checkdestiny();
			if (mc != nullptr) {
				mc->Move();
			}
		}		
	}
}