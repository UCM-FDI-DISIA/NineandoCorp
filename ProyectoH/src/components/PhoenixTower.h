#pragma once
#include "../ecs/Component.h"

class PhoenixTower : public Component {
public:

	static const cmpId id = cmpId::_PHOENIXTOWER;

	PhoenixTower(float damage, float coolingTime, float shootingTime);

	void levelUp(int level);

	bool isMaxLevel() { return isMaxLevel_; }

private:
	bool isMaxLevel_ = false;
	float coolingTime_;
	float shootingTime_;
	float elapsedTime_;
	float damage_;
};