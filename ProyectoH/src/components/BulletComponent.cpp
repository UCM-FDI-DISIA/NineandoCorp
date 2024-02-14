#include "BulletComponent.h"

BulletComponent::BulletComponent(Entity* target): targetEntity_(target){
	initComponent();
	Vector2D vel = t.getPosition() - mngr_->getComponent<Transform>(targetEntity_).getPosition();
	t.setVelocity(vel);
}

void BulletComponent::initComponent() {
	t = mngr_->getComponent<Transform>(ent_);
}

void BulletComponent::update() {
	t->translate();
	if (targetEntity_ == nullptr) {
		onTravelEnds();
	}
	else if (t->getPosition()->normalize() - targetEntity_->getPosition().normalize() <= 0) {
		onTravelEnds();
	}
}

void BulletComponent::onTravelEnds() {
	mngr_->setAlive(ent_, false);
}