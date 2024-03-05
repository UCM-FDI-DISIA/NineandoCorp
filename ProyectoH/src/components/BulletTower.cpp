#include "BulletTower.h"
#include "..//ecs/Entity.h"


BulletTower::BulletTower(float range, float reloadTime, int damage) 
	: AttackComponent::AttackComponent(range, reloadTime, damage, true), isMaxLevel_(false), secondTarget_(nullptr){}

/*void BulletTower::update() {
	AttackComponent::update();
	//if (ent_->getComponent<TowerInfo>().info_.level == ent_->getComponent<TowerInfo>().info_.maxlevel) {
	//	targetEnemy(mngr_->targetGroup, secondTarget_);
	//	//Si esta a nivel maximo lockea otro target y dispara dos balas
	//}
	if (elapsedTime_ > timeToShoot2_ && isMaxLevel_) {
		if ( secondTarget_ != nullptr) {
			shoot(secondTarget_);
			timeToShoot2_ += reloadTime_;
		}//Dispara si esta recargado y tiene target
	}
}*/

void BulletTower::levelUp(int level) {
	switch (level) {
	case 1:
		setDamage(10);
		//std::cout << "lvl1\n";
		break;
	case 2:
		setDamage(20);
		break;
	case 3:
		setDamage(35);
		break;
	case 4:
		isMaxLevel_ = true;
		break;
	default:
		break;
	}
}

void BulletTower::targetSecondEnemy(const std::list<Entity*>& targetGroup) {
	if (secondTarget_ == nullptr) {//Si no hay enemigo targeteado se busca uno
		double closestEnemy = INT32_MAX;
		for (auto enemy : targetGroup)
		{
			float distance = getDistance(mngr_->getComponent<Transform>(enemy)->getPosition());
			if (enemy != target_ && distance < range_ && distance < closestEnemy) {
				secondTarget_ = enemy;
				closestEnemy = distance;
				//std::cout << "fglskdjg";
			}
		}
	}
	else {
		if (getDistance(mngr_->getComponent<Transform>(secondTarget_)->getPosition()) > range_) {//el target ha salido de rango luego lo pierde
			secondTarget_ = nullptr;
		}
	}
}