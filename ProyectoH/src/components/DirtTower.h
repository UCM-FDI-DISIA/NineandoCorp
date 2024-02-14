#pragma once
#include "AttackComponent.h"

class DirtTower : public AttackComponent
{
public:
	DirtTower(float range, float reloadTime, int damage);
	void update() override;
};

