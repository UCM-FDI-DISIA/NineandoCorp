#include "NexusComponent.h"
#include "..//ecs/Manager.h"
#include "..//components/HealthComponent.h"

NexusComponent::NexusComponent(){ }

NexusComponent::~NexusComponent(){ }

void NexusComponent::levelUp(int level) {
	switch (level) {
	case 1:
		//damage_ = sdlutils().floatConst().at("FenixDPS1");
		break;
	case 2:
		//coolingTime_ = sdlutils().floatConst().at("FenixEnfriamiento1");
		break;
	case 3:
		//damage_ = sdlutils().floatConst().at("FenixDPS2");
		break;
	case 4:
		//coolingTime_ = sdlutils().floatConst().at("FenixEnfriamientoCero");
		break;
	}
}
