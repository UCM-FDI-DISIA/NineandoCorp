#pragma once
#include "../ecs/Component.h"
#include "../components/Transform.h"

class PhoenixTower : public Component {
public:

	static const cmpId id = cmpId::_PHOENIXTOWER;

	PhoenixTower(float damage, float coolingTime, float shootingTime, float range);

	~PhoenixTower();

	void levelUp(int level);
	void targetEnemy(const std::list<Entity*>& targetGroup);

	bool isMaxLevel() const { return isMaxLevel_; }
	float getDamage() const { return damage_; }
	float getCoolingTime()const { return coolingTime_; }
	float getShootingTime() const { return shootingTime_; }
	float getElapsedTime() const { return elapsedTime_; }
	float getRange() const { return range_; }
	bool isShooting() const { return shooting_; }
	Entity* getFire() const { return fire_; }
	Entity* getTarget() const { return target_; }

	void setElapsedTime(float elapsed) { elapsedTime_ = elapsed; }
	void setIsShooting(bool shooting) { shooting_ = shooting; }
	void setFire(Entity* fire) { fire_ = fire; }
	void setTarget(Entity* e) { target_ = e; };
	void removeFire();

protected:
	bool isMaxLevel_ = false;
	float coolingTime_;
	float shootingTime_;
	float elapsedTime_;
	float damage_;
	float range_;
	bool shooting_;
	Entity* fire_;
	Entity* target_;

	float getDistance(Vector2D targetPos);
};