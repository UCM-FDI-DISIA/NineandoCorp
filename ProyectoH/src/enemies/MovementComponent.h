#pragma once
#include "..//utils/Vector2D.h"
#include "Transform.h"
#include "..//ecs/Component.h"
class MovementComponent:public Component
{
public:
	MovementComponent(int v, bool l,Vector2D r, Entity* ent, Manager* mngr) : velocity_(v), right_(l), r_(r){};
	void update();
	void Move();
private:
	int velocity_;
	bool right_;
	bool stop_;
	Vector2D r_;
	Transform* transform_;
};