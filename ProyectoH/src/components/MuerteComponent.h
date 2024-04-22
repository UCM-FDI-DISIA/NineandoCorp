#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"
#include "Transform.h"
#include "EnemyProyectileComponent.h"
#include "RenderComponent.h"
#include "../ecs/Entity.h"

class MuerteComponent : public Component
{
public:
	static const cmpId id = cmpId::_MUERTE;
	MuerteComponent() {};

	Entity* ThrowPotion();
private:

};