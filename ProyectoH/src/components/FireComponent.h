#pragma once
#include "../ecs/Component.h"
#include "Transform.h"

class FireComponent : public Component
{
protected:
	SDL_Rect collisionRect_;
	int damage_;
	float speed_;
	Entity* target_;
	Transform* tr_;

public:
	FireComponent(Transform* tr, Entity* target, int damage, float speed);


	SDL_Rect getRect() { return collisionRect_; }
};

