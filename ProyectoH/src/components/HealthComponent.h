#pragma once
#include "..//ecs/Manager.h"
#include "..//ecs/Component.h"

class HealthComponent : public Component
{
private:
	float health_;

public:
	HealthComponent(Manager* manager_, Entity* ent_ ,float l);
	float getHealth() { return health_; };
	void addHealth(float health);
	void damage(int damage_);
};

