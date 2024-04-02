#include "RouteComponent.h"
#include "MovementComponent.h"
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
	if ((*(transform_->getPosition())-route_[destiny_])<=epsilon) {
		if (destiny_ >= route_.size()-1) {
			transform_->setVelocity({ 0,0 });
			mngr_->getComponent<MovementComponent>(ent_)->setStop(true);
		}
		else {
			destiny_++;
			changevelocity(route_[destiny_]);
			//std::cout << "e";
		}

	}
}

void
RouteComponent::changevelocity(Vector2D destino) {
	Vector2D v = destino - *(transform_->getPosition());
	v=v.normalize();
	//transform_->setVelocity(v.normalize() * transform_->getVelocity()->magnitude());
	transform_->setVelocity(v);
}
