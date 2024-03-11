
#pragma once

#include "..//ecs/Component.h"
#include "..//components/Transform.h"


class SlimeBullet : public Component
{
public:
	static const cmpId id = cmpId::_SLIMEBULLET;
	SlimeBullet(float slimeDuration, float speedDecreasePer, float slimeDPS);
	float getSpeedDecrease() const;
	float getDuration() const;
private:
	float slimeDuration_;
	float speedDecreasePer_;
	float slimeDPS_;
};

