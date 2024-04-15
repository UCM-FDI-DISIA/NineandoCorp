#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"

class MuerteComponent : public Component
{
public:
	static const cmpId id = cmpId::_MUERTE;
	MuerteComponent() {};

	Entity* ThrowPotion(Entity* target, Entity* src, float speed, Vector2D spawnPos, gameTextures texture, Vector2D bulletScale);
private:

};