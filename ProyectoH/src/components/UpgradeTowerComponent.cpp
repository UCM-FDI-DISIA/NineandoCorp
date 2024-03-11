#include "UpgradeTowerComponent.h"
#include "../ecs/Manager.h"
#include "../components/BulletTower.h"

using namespace std;

UpgradeTowerComponent::UpgradeTowerComponent(twrId id, int maxLevel) : id_(id), maxLevel_(maxLevel), currentLevel_(0) {
	//upgradeInfo_ = JSON::ParseFromFile("tower_upgrade_info.json");
}

void UpgradeTowerComponent::LevelUp() {
	if(currentLevel_ < maxLevel_)currentLevel_++;

	switch (id_) {
		case _twr_BULLET:
			mngr_->getComponent<BulletTower>(ent_)->levelUp(currentLevel_);
			break;
		case _twr_CRISTAL:

			break;
		case _twr_SLIME:

			break;
		case _twr_DIEGO:

			break;
		case _twr_FENIX:

			break;
		case _twr_CLAY:

			break;
		case _twr_POWER:

			break;
		default:

			break;
	}
}