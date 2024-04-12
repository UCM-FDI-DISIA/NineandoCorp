#include "MovementComponent.h"
void
MovementComponent::Move() {
	if (!stop_) {
		transform_->translate(speedDecrease_, speedIncrease_);
	}
	else {
		std::cout << transform_->getPosition()->getX()<<" " << transform_->getPosition()->getY();
	}
}

void
MovementComponent::MoveTo(Vector2D destino) {
	transform_->setPosition(destino);
}

void
MovementComponent::initComponent() {
	transform_ = mngr_->getComponent<Transform>(ent_);
}

void
MovementComponent::rotate(float rotation) {
	transform_->setRotation(rotation);
}

void
MovementComponent::activateSlow(float val, bool active) {
	slowed_ = active;
	speedDecrease_ = val;
}

void MovementComponent::activateAcceleration(float val, bool active)
{
	speedUp_ = active;
	speedIncrease_ = val;
}
