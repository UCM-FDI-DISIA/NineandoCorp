#include "RouteComponent.h"
#include "MovementComponent.h"
void
RouteComponent::update() {
	checkdestiny();
}

void
RouteComponent::initComponent() {
	transform_ = mngr_->getComponent<Transform>(ent_);
	route_translate.resize(route_.size());
	for (int i = 0; i < route_.size(); i++) {
		route_translate[i] = netmap->getCell(route_[i].getX(), route_[i].getY())->position;
	}
	changevelocity(route_translate[0]);
}

void
RouteComponent::checkdestiny() {
	if ((*(transform_->getPosition())- route_translate[destiny_])<=epsilon) {
		if (destiny_ >= route_translate.size()-1) {
			transform_->setVelocity({ 0,0 });
			mngr_->getComponent<MovementComponent>(ent_)->setStop(true);
		}
		else {
			destiny_++;
			changevelocity(route_translate[destiny_]);
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
