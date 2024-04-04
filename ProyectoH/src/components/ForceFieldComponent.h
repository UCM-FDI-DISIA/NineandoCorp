#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"


class ForceFieldComponent : public Component
{
public:
	static const cmpId id = cmpId::_FORCEFIELD;

	ForceFieldComponent(float forceFieldTime) : elapsedTime_(0), forceFieldTime_(forceFieldTime) {};
	SDL_Rect getRect() { return collisionRect_; }
	float getElapsedTime() { return elapsedTime_; }

	void setElapsedTime(float time) { elapsedTime_ = time; }

protected:
	SDL_Rect collisionRect_;
	float elapsedTime_;
	float forceFieldTime_;
};

