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
		if (rc != nullptr) {
			rc->checkdestiny();
			if (mc != nullptr) {
				mc->Move();
			}

		}		
	}
}