#pragma once
#include "../ecs/Component.h"
#include "../components/Transform.h"

class PhoenixTower : public Component {
public:

	static const cmpId id = cmpId::_PHOENIXTOWER;

	PhoenixTower(float damage, float coolingTime, float shootingTime, float range);

	~PhoenixTower();

	void levelUp(int level);

	bool isMaxLevel() { return isMaxLevel_; }
	float getDamage() { return damage_; }
	float getCoolingTime() { return coolingTime_; }
	float getShootingTime() { return shootingTime_; }
	float getElapsedTime() { return elapsedTime_; }
	float getRange() { return range_; }
	bool isShooting() { return shooting_; }
	Entity* getFire() { return fire_; }

	void setElapsedTime(float elapsed) { elapsedTime_ = elapsed; }
	void setIsShooting(bool shooting) { shooting_ = shooting; }
	void setFire(Entity* fire) { fire_ = fire; }
	void removeFire();
private:
	bool isMaxLevel_ = false;
	float coolingTime_;
	float shootingTime_;
	float elapsedTime_;
	float damage_;
	float range_;
	bool shooting_;
	Entity* fire_;
};