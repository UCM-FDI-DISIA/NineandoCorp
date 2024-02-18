#pragma once
#include "..//components/AttackComponent.h"
#include "BulletComponent.h"

class Entity;
class BulletTower : public AttackComponent
{
public:
	BulletTower(float range, float reloadTime, int damage);
	void shoot(Entity* targetToShoot) override;
	void levelUp(int level);
	void targetSecondEnemy(const std::vector<Entity*>& targetGroup);
private:
	Entity* secondTarget_;
	float timeToShoot2_;
	bool isMaxLevel_;
};

