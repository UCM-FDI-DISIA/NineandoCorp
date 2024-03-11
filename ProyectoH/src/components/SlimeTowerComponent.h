#include "AttackComponent.h"

#pragma once
class SlimeTowerComponent : public AttackComponent
{
public:
	static const cmpId id = cmpId::_SLIMETOWER;
	SlimeTowerComponent(float range, float slimeDuration, float speedDecreasePer, float slimeDPS, float reloadTime, float damage);
	void setSlimeDuration(float duration);
	float getDuration() const;
	void setSpeedDecrease(float percentage);
	float getSpeedDecrease() const;
private:
	float slimeDuration_;
	float speedDecreasePer_;
};

