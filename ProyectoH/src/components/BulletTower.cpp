#include "BulletTower.h"
#include "..//ecs/Entity.h"


BulletTower::BulletTower(float range, float reloadTime, int damage) 
	: AttackComponent::AttackComponent(range, reloadTime, damage, false), isMaxLevel_(false), secondTarget_(nullptr) {}

void BulletTower::targetSecondEnemy(const std::list<Entity*>& targetGroup) {
	if (secondTarget_ == nullptr) {//Si no hay enemigo targeteado se busca uno
		double closestEnemy = INT32_MAX;
		for (auto enemy : targetGroup)
		{
			float distance = getDistance(mngr_->getComponent<Transform>(enemy)->getPosition());
			if (enemy != target_ && distance < range_ && distance < closestEnemy) {
				secondTarget_ = enemy;
				closestEnemy = distance;
			}
		}
	}
	else {
		if (getDistance(mngr_->getComponent<Transform>(secondTarget_)->getPosition()) > range_) {//el target ha salido de rango luego lo pierde
			secondTarget_ = nullptr;
		}
	}
}