#include "BulletTower.h"
#include "..//ecs/Entity.h"


BulletTower::BulletTower(float range, float reloadTime, int damage) 
	: AttackComponent::AttackComponent(range, reloadTime, damage, true), isMaxLevel_(false), secondTarget_(nullptr) {}


void BulletTower::levelUp(int level) {
	switch (level) {
	case 1:
		setDamage(sdlutils().intConst().at("BalasDano1"));
		break;
	case 2:
		setDamage(sdlutils().intConst().at("BalasDano2"));
		break;
	case 3:
		setDamage(sdlutils().intConst().at("BalasDano3"));
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
			}
		}
	}
	else {
		if (getDistance(mngr_->getComponent<Transform>(secondTarget_)->getPosition()) > range_) {//el target ha salido de rango luego lo pierde
			secondTarget_ = nullptr;
		}
	}
}