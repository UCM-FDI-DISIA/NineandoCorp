#include "NexusComponent.h"
#include "..//ecs/Manager.h"
#include "..//components/HealthComponent.h"

NexusComponent::NexusComponent(){}

void NexusComponent::activateShield() { shieldActive_ = true; }

void NexusComponent::inactivateShield() { shieldActive_ = false; }

bool NexusComponent::isShieldActive() { return isShieldActive(); }
