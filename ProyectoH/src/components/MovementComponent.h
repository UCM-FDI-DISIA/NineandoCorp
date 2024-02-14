#pragma once
#include "..//ecs/Manager.h"
#include "Transform.h"
#include "..//ecs/Component.h"
class MovementComponent:public Component
{
public:
	MovementComponent() :transform_(nullptr) {};
	void update();
	void MoveTo(Vector2D destino);
	void rotate(float rotation);
	void initComponent();
private:
	Transform* transform_;
};