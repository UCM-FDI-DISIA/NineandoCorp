#include "AttackComponent.h"
#include "SDL.h"
#include "algorithm"
#include "../components/Transform.h"
#include "../components/HealthComponent.h"

AttackComponent::AttackComponent(float range, float reloadTime, int damage, bool shootBullets) : range_(range), reloadTime_(reloadTime), damage_(damage), baseDamage_(damage), elapsedTime_(reloadTime), nexo_(false) {
	target_ = nullptr; timeToShoot_ = reloadTime; loaded_ = false;
}

void AttackComponent::initComponent() {
	// A�adir mas cosas de init 
}


void AttackComponent::doDamageTo(Entity* e, float damage) {//Causa un da�o a una entidad
	Message m;
	m.id = _m_TOWER_TO_ATTACK;
	m.tower_to_attack.e = e;
	m.tower_to_attack.damage = damage;
	mngr_->send(m);
}

void AttackComponent::targetEnemy(const std::list<Entity*>& targetGroup) {//Busca un target
	if (target_ == nullptr) {//Si no hay enemigo targeteado se busca uno
		double closestEnemy = INT32_MAX;
		for (const auto& enemy : targetGroup)
		{
			if (mngr_->hasComponent<Transform>(enemy)) {
				float distance = getDistance(mngr_->getComponent<Transform>(enemy)->getPosition());
				if (distance < range_ && distance < closestEnemy) {//Si esta en rango y es el enemigo mas cercano
					target_ = enemy;
					closestEnemy = distance;
				}
			}		
		}		
	}	
	else if(target_ != nullptr && mngr_->isAlive(target_)){
		target_ = nullptr;
	}
}

float AttackComponent::getDistance(Vector2D targetPos) {//Distancia al target
	Vector2D myPos = mngr_->getComponent<Transform>(ent_)->getPosition();
	return sqrt(pow(myPos.getX() - targetPos.getX(), 2) + pow(myPos.getY() - targetPos.getY(), 2));
}

float AttackComponent::getDamage() const { return damage_; }

float AttackComponent::getBaseDamage() const { return baseDamage_; }

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

void AttackComponent::setReloadTime(float time) {
	reloadTime_ = time;
}