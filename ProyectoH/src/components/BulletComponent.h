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

public:
	static const cmpId id = cmpId::_BULLET;

	BulletComponent(Transform* tr, Entity* target, int damage);
	BulletComponent() {};
	//void initComponent() override;
	void setBullet(Entity* target, int damage) { targetEntity_ = target; damage_ = damage; };
	void doDamageTo(HealthComponent* healthcmp);
	void setDir();
	void onTravelEnds();
		
	Entity* getTarget()const { return targetEntity_; }

};