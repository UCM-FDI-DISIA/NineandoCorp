#pragma once

#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"

class AcechanteComponent : public Component
{
public:
	static const cmpId id = cmpId::_ACECHANTE;

	AcechanteComponent(float a, float r, float t): velAcceleration_(a), range_(r), elapsedTime_(0.0f), reloadTime_(t) { };
	void inRange(const std::list<Entity*>& enemyGroup);
	float getDistance(Vector2D otherPos);

	void setTime(float t) { elapsedTime_ = t; };
	float getElapsed() { return elapsedTime_; };
	float getReload() { return reloadTime_; }


private:
	float velAcceleration_;
	float range_;
	float elapsedTime_;
	float reloadTime_;
};