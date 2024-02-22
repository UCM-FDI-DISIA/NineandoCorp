#include "AttackComponent.h"
#include "SDL.h"
#include "algorithm"
#include "..//components/Transform.h"
#include "..//components/HealthComponent.h"

AttackComponent::AttackComponent(float range, float reloadTime, int damage, bool shootBullets) : range_(range), reloadTime_(reloadTime), damage_(damage){
	target_ = nullptr; timeToShoot_ = reloadTime; loaded_ = false;
}

void AttackComponent::initComponent() {
	// Añadir mas cosas de init 
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

void AttackComponent::doDamageTo(HealthComponent* healthcmp) {//Causa un daño a una entidad
	healthcmp->setHealth(healthcmp->getHealth() - damage_);
}

void AttackComponent::targetEnemy(const std::vector<Entity*>& targetGroup) {//Busca un target
	if (target_ == nullptr) {//Si no hay enemigo targeteado se busca uno
		double closestEnemy = INT32_MAX;
		for (auto enemy : targetGroup)
		{
			float distance = getDistance(mngr_->getComponent<Transform>(enemy)->getPosition());
			if(distance < range_ && distance < closestEnemy){
				target_ = enemy;
				closestEnemy = distance;
			}
		}		
	}	
	else if(mngr_->isAlive(target_)){
		if (getDistance(mngr_->getComponent<Transform>(target_)->getPosition()) > range_) {//el target ha salido de rango luego lo pierde
			target_ = nullptr;
		}
	}
}

float AttackComponent::getDistance(Vector2D targetPos) {//Distancia al target
	Vector2D myPos = mngr_->getComponent<Transform>(ent_)->getPosition();
	return sqrt(pow(myPos.getX() - targetPos.getX(), 2) + pow(myPos.getY() - targetPos.getY(), 2));
}

float AttackComponent::getDamage() const { return damage_; }

float AttackComponent::getRange() const { return range_; }

bool AttackComponent::isLoaded() const { return loaded_; }

Entity* AttackComponent::getTarget()const { return target_; }

float AttackComponent::getTimeToShoot()const { return timeToShoot_; }

float AttackComponent::getReloadTime()const { return reloadTime_; }

float AttackComponent::getElapsedTime()const { return elapsedTime_; }


void AttackComponent::setDamage(int dmg) {
	damage_ = dmg;
}
void AttackComponent::setRange(float rng) {
	range_ = rng;
}

void AttackComponent::setLoaded(bool ld) {
	loaded_ = ld;
}

void AttackComponent::setTimeToShoot(float t) {
	timeToShoot_ = t;
}

void AttackComponent::setElapsedTime(float elapsed) {
	elapsedTime_ = elapsed;
}