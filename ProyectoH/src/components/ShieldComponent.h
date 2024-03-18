#pragma once
#include "../ecs/Manager.h"
#include "..//ecs/Component.h"

class ShieldComponent : public Component
{
private:
	float currentHealth_;
	float baseHealth_;
	float maxHealth_;
public:
	static const cmpId id = cmpId::_SHIELD;
	ShieldComponent(float l);
	float getShield() { return currentHealth_; };
	void addShield(float health);
	float getMaxShield() { return maxHealth_; };
	float getBaseShield() { return baseHealth_; };
	void setMaxShield(float health);
	bool subtractShield(float health);
	void initComponent();
	void resetShield();
	void setShield(float health);
};

