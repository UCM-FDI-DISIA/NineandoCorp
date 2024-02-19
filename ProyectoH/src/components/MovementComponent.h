#pragma once
#include "..//ecs/Manager.h"
#include "Transform.h"
#include "..//ecs/Component.h"
class MovementComponent:public Component
{
public:
	static const cmpId id = cmpId::_MOVEMENT;

	MovementComponent() :transform_(nullptr) {};
	void Move();
	void MoveTo(Vector2D destino);
	void rotate(float rotation);
	void initComponent();
private:
	Transform* transform_;
};