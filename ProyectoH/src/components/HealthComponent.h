#pragma once
#include "..//ecs/Manager.h"
#include "..//ecs/Component.h"

class HealthComponent : public Component
{
private:
	float currentHealth_;
	float maxHealth_;

public:
	HealthComponent(float l);
	float getHealth() { return currentHealth_; };
	void addHealth(float health);
	void subtractHealth(float health);
	void initComponent();
	void resetHealth();
	void setHealth(float health);
	Entity* getHealthBar() { return ent_; };

};

