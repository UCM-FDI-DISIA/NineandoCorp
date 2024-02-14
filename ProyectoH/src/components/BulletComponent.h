#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"
#include "Transform.h"

class BulletComponent : public Component {
protected:
	Transform* t;
	Entity* targetEntity_;
	static cmpId id;

public:
	BulletComponent();
	
	void initComponent() override;
	void setTarget(Entity* target) { targetEntity_ = target; };
	void update() override;
	void onTravelEnds();
		
};