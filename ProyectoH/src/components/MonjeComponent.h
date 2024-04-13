
#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"
class MonjeComponent : public Component
{
public:
	static const cmpId id = cmpId::_MONJE;
	MonjeComponent() {};

	void setAttackSpeed();

private:

};
