#include "RouteComponent.h"
#include"MovementComponent.h"
void
RouteComponent::update() {
	checkdestiny();
}

void
RouteComponent::initComponent() {
	transform_ = mngr_->getComponent<Transform>(ent_);
	changevelocity(route_[0]);
}

void
RouteComponent::checkdestiny() {
	
	if (*(transform_->getPosition()) - route_[destiny_] <=epsilon) {
		if (destiny_ >= route_.size() -1) {
			transform_->setVelocity({0,0});
			mngr_->getComponent<MovementComponent>(ent_)->setStop(true);
		}
		else {
			destiny_++;
			changevelocity(route_[destiny_]);
		}

	}
}

void
RouteComponent::changevelocity(Vector2D destino) {
	transform_->setVelocity(destino - *(transform_->getPosition()));
}
