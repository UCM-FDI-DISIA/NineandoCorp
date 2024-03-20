#pragma once

#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"

class AcechanteComponent : public Component
{
public:
	static const cmpId id = cmpId::_ACECHANTE;
	AcechanteComponent(float a, float r): velAcceleration_(a), range_(r) { };
	void inRange(const std::list<Entity*>& enemyGroup);
	float getDistance(Vector2D otherPos);
private:
	float velAcceleration_;
	float range_;
};