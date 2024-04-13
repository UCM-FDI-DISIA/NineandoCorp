#include "RouteComponent.h"
#include "MovementComponent.h"


void
RouteComponent::initComponent() {
	transform_ = mngr_->getComponent<Transform>(ent_);
	renderComponent_ = mngr_->getComponent<RenderComponent>(ent_);
	changevelocity(route_[destiny_]);
}

void
RouteComponent::changeRoute(std::vector<Vector2D> route) {
	route_ = route;
	destiny_ = 0;
	changevelocity(route[destiny_]);
}

void
RouteComponent::checkdestiny() {
	if ((*(transform_->getPosition())- route_[destiny_])<=epsilon) {
		if (destiny_ >= route_.size()-1) {
			transform_->setVelocity({ 0,0 });
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
	Vector2D v = destino - *(transform_->getPosition());
	v=v.normalize();
	//transform_->setVelocity(v.normalize() * transform_->getVelocity()->magnitude());
	transform_->setVelocity(v);
	if (v.getX() > 0) {
		renderComponent_->setFlip(SDL_FLIP_NONE);
	}
	else if (v.getX() < 0) {
		renderComponent_->setFlip(SDL_FLIP_HORIZONTAL);
	}
}
