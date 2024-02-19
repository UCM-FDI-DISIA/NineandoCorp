#pragma once
#include "..//ecs/Component.h"

class NexusComponent : public Component
{
public:
	NexusComponent();
	void activateShield();
	void inactivateShield();
	bool isShieldActive();
private:
	bool shieldActive_;
};

