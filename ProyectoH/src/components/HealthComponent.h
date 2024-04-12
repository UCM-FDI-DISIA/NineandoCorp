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
	float getHealth() const { return currentHealth_; };
	void addHealth(float health);
	float getMaxHealth() const { return maxHealth_; };
	float getBaseHealth() const { return baseHealth_; };
	void setMaxHealth(float health) { maxHealth_ = health;};
	bool subtractHealth(float health);
	void initComponent();
	void resetHealth();
	void setHealth(float health) { currentHealth_ = health;}
	Entity* getHealthBar() const { return ent_; };
};

