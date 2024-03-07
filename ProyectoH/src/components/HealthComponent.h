#pragma once
#include "../ecs/Manager.h"
#include "../ecs/Component.h"

class HealthComponent : public Component
{
private:
	float currentHealth_;
	float baseHealth_;
	float maxHealth_;

public:
	static const cmpId id = cmpId::_HEALTH;
	HealthComponent(float l);
	float getHealth() { return currentHealth_; };
	void addHealth(float health);
	float getMaxHealth() { return maxHealth_; };
	float getBaseHealth() { return baseHealth_; };
	void setMaxHealth(float health);
	bool subtractHealth(float health);
	void initComponent();
	void resetHealth();
	void setHealth(float health);
	Entity* getHealthBar() { return ent_; };

};

