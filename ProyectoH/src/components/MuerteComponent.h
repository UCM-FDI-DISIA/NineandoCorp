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
	MuerteComponent(float td) : throwDuration(td), elapsedThrowTime(0) {};
	virtual ~MuerteComponent() {};

	Entity* ThrowPotion(Entity* target, Entity* src, float speed, Vector2D spawnPos, gameTextures texture, Vector2D bulletScale);

	void setElapsedTime(float n) { elapsedThrowTime = n; }
	void setThrowDuration(float n) { throwDuration = n; }

	float getElapsedTime() { return elapsedThrowTime; }
	float getThrowDuration() { return throwDuration; }
protected:
	float throwDuration;

	float elapsedThrowTime;
};