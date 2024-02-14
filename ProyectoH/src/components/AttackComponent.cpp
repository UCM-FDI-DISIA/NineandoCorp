#include "AttackComponent.h"
#include "SDL.h"
#include "algorithm"
#include "..//components/Transform.h"
#include "..//ecs/Manager.h"

AttackComponent::AttackComponent(float range, float reloadTime, int damage) : range_(range), reloadTime_(reloadTime), damage_(damage){
	target_ = nullptr; elapsedTime_ = 0; timeToShoot_ = reloadTime; loaded_ = false;
}

void AttackComponent::initComponent() {
	// Añadir mas cosas de init 
}

void AttackComponent::update() {
	//targetEnemy(mngr_->targetGroup, target_);//fija una entidad como target
	elapsedTime_ = timer_.currTime();
	if (elapsedTime_ > timeToShoot_) {
		loaded_ = true;		
		if (loaded_ && target_ != nullptr) { 
			shoot(target_); 
			timeToShoot_ += reloadTime_;
			loaded_ = false;
		}//Dispara si esta recargado y tiene target
	}	
}

void AttackComponent::targetEnemy(const std::vector<Entity*>& targetGroup, Entity* targetToLock) {//Busca un target
	if (targetToLock == nullptr) {//Si no hay enemigo targeteado se busca uno
		double closestEnemy = INT32_MAX;
	/*	for (auto enemy : targetGroup)
		{
			float distance = getDistance(enemy->getComponent<Transform>().);
			if(distance < range_ && distance < closestEnemy){
				targetToLock = enemy;
				closestEnemy = distance;
			}
		}*/		
	}	
	else {
		/*if (getDistance(target_->getComponent<Transform>().getPosition()) > range_) {
			targetToLock_ = nullptr;
		}*/
	}
}

float AttackComponent::getDistance(Vector2D targetPos) {
	Vector2D myPos = { 0,0 };//ent_->getComponent<Transform>().getPosition();
	return sqrt(pow(myPos.getX() - targetPos.getX(), 2) + pow(myPos.getY() - targetPos.getY(), 2));
}

float AttackComponent::getDamage() const { return damage_; }

float AttackComponent::getRange() const { return range_; }


