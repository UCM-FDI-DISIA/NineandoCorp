#pragma once
#include "../ecs/Component.h"
#include "Transform.h"

class FireComponent : public Component
{
protected:
	SDL_Rect collisionRect_;
	float damage_;
	float rotation_;
	float elapsedTime_=0;
	Entity* myTower_;

public:
	static const cmpId id = cmpId::_FIRE;

	FireComponent(float damage, float rot, Entity* myTower);

	SDL_Rect getRect() { return collisionRect_; }
	float getDamage() { return damage_; }
	float getRotation() { return rotation_; }
	float getElapsedTime() { return elapsedTime_; }
	Entity* getMyTower() { return myTower_; }

	void setElapsedTime(float el) { elapsedTime_ = el; }

};

