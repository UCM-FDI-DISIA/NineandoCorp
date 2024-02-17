#include "BulletTower.h"
#include "..//ecs/Entity.h"


BulletTower::BulletTower(float range, float reloadTime, int damage) 
	: AttackComponent::AttackComponent(range, reloadTime, damage, true){}

/*void BulletTower::update() {
	AttackComponent::update();
	//if (ent_->getComponent<TowerInfo>().info_.level == ent_->getComponent<TowerInfo>().info_.maxlevel) {
	//	targetEnemy(mngr_->targetGroup, secondTarget_);
	//	//Si esta a nivel maximo lockea otro target y dispara dos balas
	//}
	if (elapsedTime_ > timeToShoot2_) {
		if ( secondTarget_ != nullptr) {
			shoot(secondTarget_);
			timeToShoot2_ += reloadTime_;
		}//Dispara si esta recargado y tiene target
	}
}*/

void BulletTower::shoot(Entity* targetToShoot) {
	Entity* bullet = mngr_->addEntity(_grp_BULLETS);
	mngr_->addComponent<BulletComponent>(bullet)->setBullet(target_, damage_);
	mngr_->addComponent<Transform>(bullet);
}

