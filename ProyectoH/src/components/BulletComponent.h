#pragma once
#include "..//ecs/Component.h"
#include "Transform.h"

class BulletComponent : public Component {
protected:
	Transform* transform;
	static cmpId id;

public:
	BulletComponent(): transform(nullptr), id();
	BulletComponent(Transform* transform, Entity* ent, Manager* mngr) :transform(transform) { setContext(ent, mngr); };
	
	void initComponent() override;
	void render() override();
	void update() override;
	void onTravelEnds();
		
};