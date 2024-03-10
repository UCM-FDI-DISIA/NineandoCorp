#pragma once
#include "../ecs/Component.h"
#include "../ecs/Manager.h"
#include "FramedImage.h"

class EnhancerTower : public Component
{
public:
	static const cmpId id = cmpId::_POWERTOWER;
	EnhancerTower(float range, float damageIncrease, float healthIncrease);
	void levelUp(int level);
	float getTowersHPboost() const;
	float getDamageIncreasePercentage() const;
	float getRange() const;
	void setTowersHPboost(float hp);
	void setDamageIncreasePercentage(float damage);
private:
	float towersHPboost_;
	float damageIncreasePercentage_;
	float range_;
	bool isMaxLevel_ = false;
};

