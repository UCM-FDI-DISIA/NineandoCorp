#pragma once
#include "..//ecs/Component.h"

class NexusComponent : public Component
{
public:
	static const cmpId id = cmpId::_NEXUS;

	NexusComponent();
	void activateShield();
	void inactivateShield();
	int getShieldHitpoints() const;
	void setShieldHitpoints(int hitpoints);
	bool isShieldActive() const;
private:
	bool shieldActive_;
	int shieldCurrentHitpoints_;
};

