#include "AttackComponent.h"
#include "SDL.h"
#include "algorithm"
#include "..//components/Transform.h"
#include "..//components/HealthComponent.h"

AttackComponent::AttackComponent(float range, float reloadTime, int damage, bool shootBullets) : range_(range), reloadTime_(reloadTime), damage_(damage), shootBullets_(shootBullets){
	target_ = nullptr; elapsedTime_ = 0; timeToShoot_ = reloadTime; loaded_ = false;
}

void AttackComponent::initComponent() {
	// A�adir mas cosas de init 
}

/*void AttackComponent::update() {
	//targetEnemy(mngr_->targetGroup, target_);//fija una entidad como target
	elapsedTime_ = timer_.currTime();
	if (elapsedTime_ > timeToShoot_) {
		if (shootBullets_) {
			loaded_ = true;
			if (loaded_ && target_ != nullptr) {
				shoot(target_);
				timeToShoot_ += reloadTime_;
				loaded_ = false;
			}//Dispara si esta recargado y tiene target
		}
		else {
			loaded_ = true;
			if (loaded_ && target_ != nullptr) {
				doDamageTo(mngr_->getComponent<HealthComponent>(target_));
				timeToShoot_ += reloadTime_;
				loaded_ = false;
			}//Dispara si esta recargado y tiene target
		}
	}	
}*/

void AttackComponent::doDamageTo(HealthComponent* healthcmp) {//Causa un da�o a una entidad
	healthcmp->setHealth(healthcmp->getHealth() - damage_);
}

void AttackComponent::targetEnemy(const std::vector<Entity*>& targetGroup, Entity* targetToLock) {//Busca un target
	if (targetToLock == nullptr) {//Si no hay enemigo targeteado se busca uno
		double closestEnemy = INT32_MAX;
		/*for (auto enemy : targetgroup)
		{
			float distance = getDistance(mngr_->getComponent<Transform>(enemy)->getPosition());
			if(distance < range_ && distance < closestEnemy){
				targetToLock = enemy;
				closestEnemy = distance;
			}
		}	*/	
	}	
	else {
		if (getDistance(mngr_->getComponent<Transform>(target_)->getPosition()) > range_) {//el target ha salido de rango luego lo pierde
			targetToLock = nullptr;
		}
	}
}

float AttackComponent::getDistance(Vector2D targetPos) {//Distancia al target
	Vector2D myPos = mngr_->getComponent<Transform>(ent_)->getPosition();
	return sqrt(pow(myPos.getX() - targetPos.getX(), 2) + pow(myPos.getY() - targetPos.getY(), 2));
}

float AttackComponent::getDamage() const { return damage_; }

float AttackComponent::getRange() const { return range_; }
