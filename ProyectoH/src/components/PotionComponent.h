#pragma once
#include "..//ecs/Component.h"

class PotionComponent : public Component
{
public:
	static const cmpId id = cmpId::_POTION;

	PotionComponent(float time) : potionDuration(time), elapsedPotionTime(0), potionSpawned(false){};
	virtual ~PotionComponent() {};

	float getPotionDuration() { return potionDuration; }
	void setPotionDuration(float n) { potionDuration = n; }

	float getElapsedTime() { return elapsedPotionTime; }
	void setElapsedTime(float n) { elapsedPotionTime = n; }

	void setPotionSpawned(bool b) { potionSpawned = b; }
	bool hasPotionSpawned() { return potionSpawned; }

protected:
	float potionDuration;
	float elapsedPotionTime;
	bool potionSpawned;
};

