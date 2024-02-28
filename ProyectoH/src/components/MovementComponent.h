#pragma once
#include "..//ecs/Manager.h"
#include "Transform.h"
#include "..//ecs/Component.h"
class MovementComponent:public Component
{
public:
	static const cmpId id = cmpId::_MOVEMENT;

	MovementComponent() :transform_(nullptr),stop_(false) {};
	void Move();
	void MoveTo(Vector2D destino);
	void rotate(float rotation);
	void initComponent();
	void setStop(bool);
	bool getStop() { return stop_; };
private:
	bool stop_;
	Transform* transform_;
};