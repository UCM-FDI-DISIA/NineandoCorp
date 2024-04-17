#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"
class PrincipitoComponent : public Component
{
public:
	static const cmpId id = cmpId::_PRINCIPITO;
	PrincipitoComponent(float a): attackvelocity(a){};

	void setAttackSpeed();
	void ResetVelocity();

private:
	float attackvelocity;
};