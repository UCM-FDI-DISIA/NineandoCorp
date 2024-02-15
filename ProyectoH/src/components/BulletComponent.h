#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"
#include "Transform.h"
#include "HealthComponent.h"

class BulletComponent : public Component {
protected:
	Transform* t;
	Entity* targetEntity_;
	static cmpId id;
	int damage_;

public:
	BulletComponent();
	
	void initComponent() override;
	void setBullet(Entity* target, int damage) { targetEntity_ = target; damage_ = damage; };
	void update() override;
	void doDamageTo(HealthComponent* healthcmp);
	void onTravelEnds();
		
};