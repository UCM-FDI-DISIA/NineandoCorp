#include "MovementComponent.h"
void
MovementComponent::Move() {
	if (!stop_) {
		transform_->translate();
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
MovementComponent::setStop(bool stop) {
	stop_ = stop;
}