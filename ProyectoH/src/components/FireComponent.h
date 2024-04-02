#pragma once
#include "../ecs/Component.h"
#include "Transform.h"

class FireComponent : public Component
{
protected:
	SDL_Rect collisionRect_;
	float damage_;
	float baseDamage_;
	float rotation_;
	float elapsedTime_=0;
	Entity* myTower_;

public:
	static const cmpId id = cmpId::_FIRE;

	FireComponent(float damage, float rot, Entity* myTower);

	SDL_Rect getRect() const { return collisionRect_; }
	float getDamage() const { return damage_; }
	float getBaseDamage() const { return baseDamage_; }
	void setDamage(float dmg) { damage_ = dmg; }
	void resetDamage() { damage_ = baseDamage_; }
	float getRotation() const { return rotation_; }
	float getElapsedTime() const { return elapsedTime_; }
	Entity* getMyTower() const { return myTower_; }

	void setElapsedTime(float el) { elapsedTime_ = el; }

};

