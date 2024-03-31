#include "AngelComponent.h"

float AngelComponent::getDistance(Vector2D otherPos) {
	Vector2D myPos = mngr_->getComponent<Transform>(ent_)->getPosition();
	return sqrt(pow(myPos.getX() - otherPos.getX(), 2) + pow(myPos.getY() - otherPos.getY(), 2));
}