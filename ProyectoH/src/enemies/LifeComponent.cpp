#include "LifeComponent.h"

LifeComponent::LifeComponent(Manager* m, Entity* e, int l) : life_(l) { Component::setContext(e, m); };

void LifeComponent::damage(int d_) {
	life_ -= d_;
	if (life_ <= 0) {
		mngr_->setAlive(ent_, false);
	}
}