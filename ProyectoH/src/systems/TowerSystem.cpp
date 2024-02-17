#include "TowerSystem.h"
#include "../ecs/Manager.h"
#include "../components/AttackComponent.h"

TowerSystem::TowerSystem()  {

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

	for (auto& t : towers) {
		mngr_->getComponent<Transform>(t)->update();
		mngr_->getComponent<AttackComponent>(t)->update();
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