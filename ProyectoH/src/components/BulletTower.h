#pragma once
#include "..//components/AttackComponent.h"
#include "BulletComponent.h"

class Entity;
class BulletTower : public AttackComponent
{
public:
	BulletTower(float range, float reloadTime, int damage);
	void levelUp(int level);
	void targetSecondEnemy(const std::list<Entity*>& targetGroup);

	bool isMaxLevel() { return isMaxLevel_; }
	Entity* getSecondTarget() { return secondTarget_; }

private:
	Entity* secondTarget_;
	float timeToShoot2_;
	bool isMaxLevel_;
};

