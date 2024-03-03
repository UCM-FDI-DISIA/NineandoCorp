#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"
#include "Transform.h"
#include "HealthComponent.h"

class BulletComponent : public Component {
protected:
	Transform* t;
	Entity* targetEntity_;
	int damage_;
	float speed_;

public:
	static const cmpId id = cmpId::_BULLET;

	BulletComponent(Transform* tr, Entity* target, int damage, float speed);
	BulletComponent() {};
	//void initComponent() override;
	void setBullet(Entity* target, int damage) { targetEntity_ = target; damage_ = damage; };
	void doDamageTo(Entity* e, float damage);
	void setDir();
	void onTravelEnds();

	float getDamage()const { return damage_; }
		
	Entity* getTarget()const { return targetEntity_; }

};