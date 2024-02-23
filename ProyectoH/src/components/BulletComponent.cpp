#include "BulletComponent.h"

BulletComponent::BulletComponent(): targetEntity_(nullptr){
	Vector2D vel = *(t->getPosition()) - *(mngr_->getComponent<Transform>(targetEntity_)->getPosition());
	t->setVelocity(vel);
}

void BulletComponent::initComponent() {
	t = mngr_->getComponent<Transform>(ent_);
}

void BulletComponent::doDamageTo(HealthComponent* healthCmp){
	healthCmp->subtractHealth(damage_);
}

void BulletComponent::onTravelEnds() {
	mngr_->setAlive(ent_, false);
}