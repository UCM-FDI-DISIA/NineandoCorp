#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"
#include "Transform.h"
#include "HealthComponent.h"

class BulletComponent : public Component {
protected:
	Transform* t;
	Entity* targetEntity_;
	Entity* srcEntity;
	int damage_;
	float speed_;

public:
	static const cmpId id = cmpId::_BULLET;

	BulletComponent(Transform* tr, Entity* target, Entity* src, int damage, float speed);
	BulletComponent() {};
	void doDamageTo(Entity* e, float damage);
	void setDir();
	void onTravelEnds();

	float getDamage()const { return damage_; }
		
	Entity* getTarget()const { return targetEntity_; }

};