#pragma once

#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"

class AcechanteComponent : public Component
{
public:
	static const cmpId id = cmpId::_ACECHANTE;

	AcechanteComponent(float a, float r, float t): velAcceleration_(a), range_(r), elapsedTime_(0.0f), reloadTime_(t), attAnimation_(false) { };
	void inRange(const std::list<Entity*>& enemyGroup);
	float getDistance(Vector2D otherPos);

	void setTime(float t) { elapsedTime_ = t; };
	float getElapsed() const{ return elapsedTime_; };
	float getReload() const{ return reloadTime_; }
	bool getAtt() { return attAnimation_; };
	void setAtt(bool a_) { attAnimation_ = a_; };

private:
	float velAcceleration_;
	float range_;
	float elapsedTime_;
	float reloadTime_;
	bool attAnimation_;
};