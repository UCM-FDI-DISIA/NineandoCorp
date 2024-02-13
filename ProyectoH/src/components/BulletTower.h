#pragma once
#include "AttackComponent.h"

class Entity;
class BulletTower : public AttackComponent
{
public:
	BulletTower(float range, float reloadTime, int damage);
	void update() override;
	void shoot() override;
private:
	Entity* secondTarget_;
};

