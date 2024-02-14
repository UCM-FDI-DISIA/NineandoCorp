#pragma once
#include "..//ecs/Component.h"
#include "Transform.h"

class BulletComponent : public Component {
protected:
	Transform* t;
	Entity* targetEntity_;
	static cmpId id;

public:
	BulletComponent(Entity* target);
	
	void initComponent() override;
	void update() override;
	void onTravelEnds();
		
};