#include "NexusComponent.h"
#include "..//ecs/Manager.h"
#include "..//components/HealthComponent.h"

NexusComponent::NexusComponent():shieldCurrentHitpoints_(0) { shieldActive_ = false; }

void NexusComponent::activateShield() { 
	shieldActive_ = true; 
	//mngr_->getComponent<HealthComponent>(ent_)->addHealth(shieldCurrentHitpoints_);
}

void NexusComponent::inactivateShield() { 
	shieldActive_ = false;
	//mngr_->getComponent<HealthComponent>(ent_)->subtractHealth(shieldCurrentHitpoints_);
}

bool NexusComponent::isShieldActive() const { return shieldActive_; }

int NexusComponent::getShieldHitpoints() const { return shieldCurrentHitpoints_; }

void NexusComponent::setShieldHitpoints(int hitpoints) { shieldCurrentHitpoints_ = hitpoints; }
