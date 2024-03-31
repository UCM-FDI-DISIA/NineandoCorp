#pragma once
#include "../ecs/Component.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"

class AngelComponent : public Component
{
public:
	static const cmpId id = cmpId::_ANGEL;
	AngelComponent(float range) : range_(range), elapsedTime_(0) {};

	float getElapsed() { return elapsedTime_; }
	float getRange() { return range_; }
	float getDistance(Vector2D otherPos);

	void setElapsed(float elapsed) { elapsedTime_ = elapsed; }
private:
	float elapsedTime_;
	float range_;
};

