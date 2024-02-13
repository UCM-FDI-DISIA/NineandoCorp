#pragma once
#include "..//ecs/Component.h"
#include "..//sdlutils/VirtualTimer.h"
#include "..//utils/Vector2D.h"

class Entity;
class TowerAttackComponent : public Component
{
public:
	TowerAttackComponent(float range, float reloadTime, int damage);
	virtual void update() override;
private:
	virtual void shoot() {};
	float getDistance(Vector2D enemyPos);
	void targetEnemy();
	float elapsedTime;
	float range;
	float reloadTime;
	float timeToShoot;
	int damage;
	Entity* enemy;
	VirtualTimer timer;
};

