#pragma once
#include "../ecs/Manager.h"
#include "..//ecs/Component.h"
#include "..//ecs/Entity.h"

class ShieldComponent : public Component
{
private:
	float currentHealth_;
	float baseHealth_;
	float maxHealth_;
	Entity* imgShield_;
	
public:
	static const cmpId id = cmpId::_SHIELD;
	ShieldComponent(float l);
	virtual ~ShieldComponent() {
		mngr_->setAlive(imgShield_, false);
	}
	float getShield() { return currentHealth_; };
	void addShield(float health);
	float getMaxShield() { return maxHealth_; };
	float getBaseShield() { return baseHealth_; };
	Entity* getImg() { return imgShield_; }
	void setImg(Entity* ent) { imgShield_ = ent; };
	void setMaxShield(float health);
	void subtractShield(float health);
	void initComponent();
	void resetShield();
	void setShield(float health);
	
	
};

