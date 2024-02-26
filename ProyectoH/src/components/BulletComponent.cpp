#include "BulletComponent.h"

BulletComponent::BulletComponent(Transform* tr, Entity* target, int damage):t(tr), targetEntity_(target), damage_(damage){
	//initComponent();
	
}

//void BulletComponent::initComponent() {
//	t = mngr_->getComponent<Transform>(ent_);
//}

void BulletComponent::doDamageTo(HealthComponent* healthCmp){
	healthCmp->subtractHealth(damage_);
}

void BulletComponent::onTravelEnds() {
	mngr_->setAlive(ent_, false);
}

void BulletComponent::setDir() {
	Vector2D vel = *(mngr_->getComponent<Transform>(targetEntity_)->getPosition()) - *(t->getPosition());
	t->setVelocity(vel);
}