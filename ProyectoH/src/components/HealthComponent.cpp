#include "HealthComponent.h"

HealthComponent::HealthComponent(Manager* m, Entity* e, float l) : health_(l) { Component::setContext(e, m); };


void
HealthComponent::addHealth(float health) {
	health_ += health;
}

void
HealthComponent::subtractHealth(float health) {
	health_ -= health;
	if (health_ <= 0) {
		mngr_->setAlive(ent_, false);
	}
}