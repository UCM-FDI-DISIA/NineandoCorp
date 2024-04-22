#pragma once
#include "../ecs/Component.h"

class PotionComponent : public Component
{
public:
	static const cmpId id = cmpId::_POTION;

	PotionComponent(float time) :potionDuration_(time), elapsed_(0), potionSpawned_(false) {}
	virtual ~PotionComponent(){}


	float getPotionDuration() { return potionDuration_; }
	void setPotionDuration(float time) { potionDuration_ = time; }
	float getElapsedTime() { return elapsed_; }
	void setElapsedTime(float n) { elapsed_ = n; }

	void setPotionSpawned(bool b) { potionSpawned_ = b; }
	bool hasPotionSpawned() { return potionSpawned_; }
protected:
	float elapsed_;
	float potionDuration_;
	bool potionSpawned_;
};

