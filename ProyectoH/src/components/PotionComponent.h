#pragma once
#include "..//ecs/Component.h"

class PotionComponent : public Component
{
public:
	static const cmpId id = cmpId::_POTION;

	PotionComponent(Entity* target, Entity* src, float speed, Vector2D spawnPos, gameTextures texture, Vector2D bulletScale, float time);
protected:
	float potionDuration;
	float getPotionDuration() { return potionDuration; }
	float setPotionDuration(float n) { potionDuration = n; }

	float elapsedPotionTime;
	float getElapsedTime() { return elapsedPotionTime; }
	float setElapsedTime(float n) { elapsedPotionTime = n; }
	
	void SpawnArea();
};

