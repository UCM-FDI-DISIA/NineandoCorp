#include "DirtTower.h"

DirtTower::DirtTower()
	: AttackComponent::AttackComponent(0, 0, 0, false) {}

void DirtTower::levelUp(int level) {
	HealthComponent* h = mngr_->getComponent<HealthComponent>(ent_);
	if (h != nullptr) {
		/*switch (level) {
		case 1:
			h->setMaxHealth(sdlutils().floatConst().at("ArcillaVida1"));
			break;
		case 2:
			h->setMaxHealth(sdlutils().floatConst().at("ArcillaVida2"));
			break;
		case 3:
			h->setMaxHealth(sdlutils().floatConst().at("ArcillaVida3"));
			break;
		case 4:
			h->setMaxHealth(sdlutils().floatConst().at("ArcillaVida4"));
			isMaxLevel_ = true;
			break;
		default:
			break;
		}*/
		h->setHealth(h->getMaxHealth());
	}	
}