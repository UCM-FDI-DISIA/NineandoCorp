#pragma once
#include "../ecs/Component.h"
#include "../ecs/Manager.h"
#include "FramedImage.h"

class EnhancerTower : public Component
{
public:
	static const cmpId id = cmpId::_POWERTOWER;
	EnhancerTower(float range, float damageIncrease, float healthIncrease);
	float getTowersHPboost() const { return towersHPboost_; };
	float getDamageIncreasePercentage()  const { return damageIncreasePercentage_; };
	float getRange() const { return range_; };
	void setTowersHPboost(float hp) { towersHPboost_ = hp; };
	void setDamageIncreasePercentage(float damage) { damageIncreasePercentage_ = damage; };
private:
	float towersHPboost_;
	float damageIncreasePercentage_;
	float range_;
	bool isMaxLevel_ = false;
};

