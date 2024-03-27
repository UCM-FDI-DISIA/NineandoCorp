#include "AcechanteComponent.h"
#include "algorithm"
#include "../components/Transform.h"
#include "../components/MovementComponent.h"

void AcechanteComponent::inRange(const std::list<Entity*>& enemyGroup)
{
	for (const auto& enemy : enemyGroup) {
		if (getDistance(mngr_->getComponent<Transform>(enemy)->getPosition()) < range_) {
			mngr_->getComponent<MovementComponent>(enemy)->activateAcceleration(velAcceleration_);
		}
	}
	std::cout << "velocidad";
	
}

float AcechanteComponent::getDistance(Vector2D otherPos)
{
	Vector2D myPos = mngr_->getComponent<Transform>(ent_)->getPosition();
	return sqrt(pow(myPos.getX() - otherPos.getX(), 2) + pow(myPos.getY() - otherPos.getY(), 2));
}
