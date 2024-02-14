#pragma once
#include "..//components/AttackComponent.h"

class Entity;
class BulletTower : public AttackComponent
{
public:
	BulletTower(float range, float reloadTime, int damage);
	void update() override;
	void shoot(Entity* targetToShoot) override;
private:
	Entity* secondTarget_;
	float timeToShoot2_;
};

