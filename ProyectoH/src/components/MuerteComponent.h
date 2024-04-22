#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"

class MuerteComponent : public Component
{
public:
	static const cmpId id = cmpId::_MUERTE;
	MuerteComponent() {};

	void ThrowPotion();
private:

};