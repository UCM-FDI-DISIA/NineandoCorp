#pragma once
#include "..//ecs/Component.h"

class PotionComponent : public Component
{
public:
	static const cmpId id = cmpId::_POTION;

	PotionComponent(float time) : potionDuration(time), elapsedPotionTime(0){};
	virtual ~PotionComponent() {};

protected:
	float potionDuration;
	float getPotionDuration() { return potionDuration; }
	float setPotionDuration(float n) { potionDuration = n; }

	float elapsedPotionTime;
	float getElapsedTime() { return elapsedPotionTime; }
	float setElapsedTime(float n) { elapsedPotionTime = n; }
	
	void SpawnArea();
};

