#pragma once
#include "..//ecs/Component.h"

class TowerAttackComponent : public Component
{
public:
	TowerAttackComponent();
	virtual void update() override;
private:
	virtual void shoot();
	float range;
	float reloadTime;
};

