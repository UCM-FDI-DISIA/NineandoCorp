#include "BulletComponent.h"

BulletComponent::BulletComponent(): targetEntity_(nullptr){
	initComponent();
	Vector2D vel = *(t->getPosition()) - *(mngr_->getComponent<Transform>(targetEntity_)->getPosition());
	t->setVelocity(vel);
}

void BulletComponent::initComponent() {
	t = mngr_->getComponent<Transform>(ent_);
}

void BulletComponent::update() {
	t->translate();
	if (targetEntity_ == nullptr) {
		onTravelEnds();
	}
	else if ((*(t->getPosition()) - *(mngr_->getComponent<Transform>(targetEntity_)->getPosition())).magnitude() <= 0.1f) {
		doDamageTo(mngr_->getComponent<HealthComponent>(targetEntity_));
		onTravelEnds();
	}
}

void BulletComponent::doDamageTo(HealthComponent* healthCmp){
	healthCmp->setHealth(healthCmp->getHealth() - damage_);
}

void BulletComponent::onTravelEnds() {
	mngr_->setAlive(ent_, false);
}