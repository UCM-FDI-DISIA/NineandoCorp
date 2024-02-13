#pragma once
#include "..//ecs/Component.h"
#include "..//sdlutils/VirtualTimer.h"
#include "..//utils/Vector2D.h"

class Entity;
class AttackComponent : public Component
{
public:
	AttackComponent(float range, float reloadTime, int damage);
	virtual void update() override;
private:
	virtual void shoot() {};
	float getDistance(Vector2D targetPos);
	void targetEnemy();
	float elapsedTime_;
	float range_;
	float reloadTime_;
	float timeToShoot_;
	int damage_;
	Entity* target_;
	VirtualTimer timer_;
};

