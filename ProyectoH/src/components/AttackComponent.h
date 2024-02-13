#pragma once
#include "..//ecs/Component.h"
#include "..//sdlutils/VirtualTimer.h"
#include "..//utils/Vector2D.h"
#include <vector>

class Entity;
class AttackComponent : public Component
{
public:
	AttackComponent(float range, float reloadTime, int damage);
	virtual void update() override;
protected:
	void targetEnemy(const std::vector<Entity*>& targetGroup, Entity* targetToLock);
private:
	virtual void shoot(Entity* targetToShoot) {};
	float getDistance(Vector2D targetPos);
	float elapsedTime_;
	float range_;
	float reloadTime_;
	float timeToShoot_;
	int damage_;
	Entity* target_;//target principal
	VirtualTimer timer_;//contador para tiempo de ataque
};

