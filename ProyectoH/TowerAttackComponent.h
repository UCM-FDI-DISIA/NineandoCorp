#pragma once

#include "src/ecs/Component.h"

class TowerAttackcomponent : public Component
{
	float reload;
	float range;
	virtual void shoot();
public:
	TowerAttackcomponent();
	virtual void update() override;

};
