#include "UpgradeTowerComponent.h"
#include "../ecs/Manager.h"
#include "../components/BulletTower.h"
#include "..//components/EnhancerTower.h"
#include "..//components/CrystalTower.h"
#include "..//components/RenderComponent.h"
#include "..//components/DiegoSniperTower.h"
#include "..//components/PhoenixTower.h"
#include "..//components/DirtTower.h"
#include "..//components/SlimeTowerComponent.h"

using namespace std;

UpgradeTowerComponent::UpgradeTowerComponent(twrId id, int maxLevel) : id_(id), maxLevel_(maxLevel), currentLevel_(1) {
	//upgradeInfo_ = JSON::ParseFromFile("tower_upgrade_info.json");
}

void UpgradeTowerComponent::levelUp() {
	auto fi = mngr_->getComponent<FramedImage>(ent_);
	if (currentLevel_ < maxLevel_) {
		fi->setCurrentFrame(fi->getCurrentFrame() + 1);
		auto tr = mngr_->getComponent<Transform>(ent_);
		//Vector de ajuste debido al desplazamiento causado por el spritesheet
		Vector2D adjustOffset = Vector2D(3.0f * currentLevel_, 0);

		tr->setPosition(*tr->getPosition() - adjustOffset);
		currentLevel_++;
	}
	if (currentLevel_ == 0) { currentLevel_ = 1; }
	
	switch (id_) {
		case _twr_BULLET:
			mngr_->getComponent<BulletTower>(ent_)->levelUp(currentLevel_);
			break;
		case _twr_CRISTAL:
			mngr_->getComponent<CrystalTower>(ent_)->levelUp(currentLevel_);
			break;
		case _twr_SLIME:
			mngr_->getComponent<SlimeTowerComponent>(ent_)->levelUp(currentLevel_);
			break;
		case _twr_DIEGO:
			mngr_->getComponent<DiegoSniperTower>(ent_)->levelUp(currentLevel_);
			break;
		case _twr_FENIX:
			mngr_->getComponent<PhoenixTower>(ent_)->levelUp(currentLevel_);
			break;
		case _twr_CLAY:
			mngr_->getComponent<DirtTower>(ent_)->levelUp(currentLevel_);
			break;
		case _twr_POWER:
			mngr_->getComponent<EnhancerTower>(ent_)->levelUp(currentLevel_);
			break;
		default:
			break;
	}
}