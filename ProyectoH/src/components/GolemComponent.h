#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"
class GolemComponent: public Component
{
public:
	static const cmpId id = cmpId::_GOLEM;
	GolemComponent() :cura_(10.0f),reloadTime_(1.0f), elapsedTime_(0.0f){  };
	void Regenera();
private:
	float cura_;
	float reloadTime_;
	float elapsedTime_;
};

