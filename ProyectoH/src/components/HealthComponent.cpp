#include "HealthComponent.h"

HealthComponent::HealthComponent(Manager* m, Entity* e, float l) : health_(l) { Component::setContext(e, m); };

void 
HealthComponent::damage(int d_) {
	health_ -= d_;
	if (health_ <= 0) {
		mngr_->setAlive(ent_, false);
	}
}

void
HealthComponent::addHealth(float health) {
	health_ += health;
}

void
HealthComponent::subtractHealth(float health) {
	health_ -= health;
}