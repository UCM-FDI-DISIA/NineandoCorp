#include "AttackComponent.h"
#include "SDL.h"
#include "algorithm"
#include "../components/Transform.h"
#include "../components/HealthComponent.h"

AttackComponent::AttackComponent(float range, float reloadTime, int damage, bool towers) : range_(range), reloadTime_(reloadTime), damage_(damage), baseDamage_(damage),towers_(towers), elapsedTime_(reloadTime), nexo_(true) {
	target_ = nullptr; timeToShoot_ = reloadTime; loaded_ = false; isAttacking = false;
}

void AttackComponent::initComponent() {
	// A�adir mas cosas de init 
}


void AttackComponent::doDamageTo(Entity* e, float damage, hdlrId targetId) {//Causa un da�o a una entidad
	Message m;
	m.id = _m_ENTITY_TO_ATTACK;
	m.entity_to_attack.e = e;
	m.entity_to_attack.damage = damage;
	m.entity_to_attack.targetId = targetId;
	m.entity_to_attack.src = ent_;
	mngr_->send(m);
}

void AttackComponent::targetFromGroup(const std::list<Entity*>& targetGroup) {//Busca un target
	if (target_ == nullptr) {//Si no hay enemigo targeteado se busca uno
		double closestTarget = INT32_MAX;
		for (const auto& target : targetGroup)
		{
			if (mngr_->hasComponent<Transform>(target)) {
				float distance = getDistance(mngr_->getComponent<Transform>(target)->getPosition());
				if (distance < range_ && distance < closestTarget) {//Si esta en rango y es el enemigo mas cercano
					target_ = target;
					closestTarget = distance;
				}
			}		
		}		
	}	
	else if(!mngr_->isAlive(target_)){
		target_ = nullptr;
	}
}

float AttackComponent::getDistance(Vector2D targetPos) {//Distancia al target
	Vector2D myPos = mngr_->getComponent<Transform>(ent_)->getPosition();
	return sqrt(pow(myPos.getX() - targetPos.getX(), 2) + pow(myPos.getY() - targetPos.getY(), 2));
}

bool AttackComponent::getAttack() const {
	return isAttacking;
}
