#pragma once
#include "..//ecs/Manager.h"
#include "Transform.h"
#include "..//ecs/Component.h"
class MovementComponent:public Component
{

public:
	static const cmpId id = cmpId::_MOVEMENT;

	MovementComponent() :transform_(nullptr),stop_(false), slowed_(false), speedDecrease_(0) {};
	void MoveTo(Vector2D destino);
	void rotate(float rotation);
	void initComponent();
	void Move();
	void setStop(bool stop);
	void activateSlow(float val, bool active);
	bool getSlow() const{ return slowed_; }
	bool getStop() const{ return stop_; };
private:
	Transform* transform_;
	bool stop_;
	bool slowed_;
	float speedDecrease_;
};