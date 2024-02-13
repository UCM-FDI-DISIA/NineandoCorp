#pragma once
#include "..//ecs/Manager.h"
#include "..//ecs/Component.h"

class LifeComponent : public Component
{
private:
	int life_;

public:
	LifeComponent(Manager* manager_, Entity* ent_ ,int l);
	int getLifes() { return life_; };
	void damage(int damage_);
};

